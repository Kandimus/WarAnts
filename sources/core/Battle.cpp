#include "Battle.h"

#include "Log.h"

#include "AntFabric.h"
#include "constants.h"
#include "Cell.h"
#include "Config.h"
#include "Map.h"
#include "MapMath.h"
#include "Player.h"
#include "VirtualMachine.h"

#include "battlelog/BattleLogService.h"
#include "battlelog/FileProvider.h"
#include "battlelog/TextScreenProvider.h"

namespace WarAnts
{

Battle::Battle(const std::string& confname, const std::string& mapname, const std::vector<std::string>& players)
{
    m_conf = std::make_shared<Config>(Constant::dirConfig + confname);
    m_conf->setUBID(createUBID());
    su::Log::instance().setTimeStamp(false);
    su::Log::instance().setFilename(m_conf->UBID());

    // init ant fabric
    AntFabric::init(m_conf->antsFileSettings());

    // create the player list
    uint32_t player_index = 0;
    for (auto& libname : players)
    {
        m_players.push_back(std::make_shared<Player>(player_index++, Constant::dirPlayers + libname));
    }

    if (players.size() < 2)
    {
        LOGE("Count of players must be greater than 1"); 
        return;
    }

    for (auto& player : m_players)
    {
        if (!player->isInit())
        {
            LOGE("Player '%s' [%s] is not initiliazed", player->teamName().c_str(), player->library().c_str());
            return;
        }
    }

    // check players names
    for (int ii = 0; ii < m_players.size() - 1; ++ii)
    {
        uint32_t count = 1;

        for (int jj = ii + 1; jj < m_players.size(); ++jj)
        {
            if (m_players[ii]->teamName() == m_players[jj]->teamName())
            {
                m_players[jj]->changeTeamName(count++);
            }
        }
    }

    std::string logDir = su::Log::instance().getDir();
    m_logService = std::make_shared<BattleLogService>();
    m_logService->add(std::make_shared<FileProvider>(logDir + m_conf->UBID() + ".json"));
    m_logService->add(std::make_shared<TextScreenProvider>(logDir + m_conf->UBID() + "_screen.txt"));

    //TODO может быть перенести карту в функцию `run`?
    m_map = std::make_shared<Map>(m_conf, mapname);
    LOGI("Created new battle [%s]", m_conf->UBID().c_str());

    m_isInit = true;
}

size_t getTickCount()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

struct TickCountClock
{
    typedef std::chrono::duration<size_t, std::milli> duration;
    typedef std::chrono::time_point<TickCountClock> time_point;
    static const bool is_steady = true;

    static time_point now() noexcept
    {
        return time_point(duration(getTickCount()));
    }
};

std::string Battle::createUBID() const
{
    std::time_t t = std::time(nullptr);
    std::tm dt;

    localtime_s(&dt, &t);
    return su::String_format2("%04i%02i%02i-%02i%02i%02i",
        dt.tm_year + 1900, dt.tm_mon + 1, dt.tm_mday,
        dt.tm_hour, dt.tm_min, dt.tm_sec);
}

int Battle::run()
{
    if (!m_isInit)
    {
        LOGE("Can't start the battle. Battle is not initialized");
        return 1;
    }

    // create list of all ant
    m_ants = m_map->generate(m_players);

    // send of starting info
    m_logService->saveMapInfo(*m_map.get());
    for (auto& player : m_players)
    {
        m_logService->savePlayer(*player.get());
    }
    m_logService->saveMap(*m_map.get());

    m_iteration = 0;

    // main loop
    while(true)
    {
        //---------------------------------------------------------------------
        // Start of iteration
        auto timeStart = getTickCount();

        // clear IsChange flag
        m_map->clearChanged();

        LOGD("Iteration %i", m_iteration);

        // randomize the list of ants
        VectorAnts ant_vec(m_ants.begin(), m_ants.end());
        std::shuffle(ant_vec.begin(), ant_vec.end(), Math::randGenerator());

        // save log
        m_logService->saveBeginTurn(m_iteration);

        //---------------------------------------------------------------------
        // Ant phase
        for (auto& ant : ant_vec)
        {
            if (ant->status() == Ant::Status::Dead)
            {
                continue;
            }

            ant->beginTurn();

            processingInterrupt(*ant);

            if(ant->interruptReason())
            {
                VirtualMachine vm(m_iteration, m_map, ant);
                vm.run();
                ant->postVM();
            }

            doAntCommand(*ant);
            m_map->forceCellChange(ant->position());

            // Ant has been died
            if (!ant->endTurn())
            {
                killAnt(*ant.get());
            }
        } // ants

        // delete dead ants
        for (auto pAnt = m_ants.begin(); pAnt != m_ants.end(); )
        {
            if ((*pAnt)->status() == Ant::Status::Dead)
            {
                pAnt = m_ants.erase(pAnt);
            }
            else
            {
                ++pAnt;
            }
        }

        m_logService->saveEndTurn(m_iteration, getTickCount() - timeStart);

        if (m_ants.empty() || checkEndGame())
        {
            break;
        }

        //---------------------------------------------------------------------
        // End of iteration
        m_logService->saveMap(*m_map.get());

        m_iteration++;
    }

    // TODO print RESULT file
    if (m_winner)
    {
        LOGD("'%s' #%i win!", m_winner->teamName().c_str(), m_winner->index());
    }
    else
    {
        LOGD("DRAW. All ants are dead!");
    }

    m_logService->endGame(m_winner);

    return 0;
}

void Battle::processingInterrupt(Ant& ant)
{
    if (ant.interruptFlags() & Interrupt::CloseEnemy)
    {
        bool enemyIsPresent = false;
        auto player = ant.player();
        auto result = m_map->processingAntsInRadius(ant.position(), ant.visibility() / Constant::DivCloseRadius, [&enemyIsPresent, player](Ant* cellAnt)
        {
            enemyIsPresent = cellAnt->player()->index() != player->index();
        });
        ant.setInterruptReason(Interrupt::CloseEnemy, enemyIsPresent);
    }

    if (ant.interruptFlags() & Interrupt::FarEnemy)
    {
        bool enemyIsPresent = false;
        auto player = ant.player();
        auto result = m_map->processingAntsInRadius(ant.position(), ant.visibility() / Constant::DivFarRadius, [&enemyIsPresent, player](Ant* cellAnt)
        {
            enemyIsPresent = cellAnt->player()->index() != player->index();
        });
        ant.setInterruptReason(Interrupt::FarEnemy, enemyIsPresent);
    }

    if (ant.interruptFlags() & Interrupt::CloseFood)
    {
    }

    if (ant.interruptFlags() & Interrupt::FarFood)
    {

    }

    // Queen has been attacked!

    if (ant.interruptReason())
    {
        LOGD("%s have %sintrrupt 0x%04x", ant.toString().c_str(), ant.interruptReason() & ant.interruptFlags() ? "" : "masked ", ant.interruptReason());
    }
}

void Battle::doAntCommand(Ant& ant)
{
    auto cmd = ant.command();

    // If the last command is completed, but player doesn't set a new command,
    // then the Idle command is temporarily forced for 1 turn
    if (cmd.isCompleted())
    {
        cmd.set(Command::Idle, Position(0, 0), 1);
    }

    switch(cmd.m_type)
    {
        case Command::Idle: commandIdle(ant); break;
        case Command::MovePos: commandMove(ant); break;
        case Command::Attack: commandAttack(ant); break;
        //case CommandType::MoveAndIdle: commandMoveAndIdle(ant); break;
        //case CommandType::MoveAndAttack: commandMoveAndAttack(ant);break;
//		case CommandType::MoveToFood: doAntMoveToFood(ant); break;
//		case CommandType::Attack: doAntAttack(ant); break;
//		case CommandType::MoveAndAttack: doAntMoveAndAttack(ant); break;
//		case CommandType::Feed: doAntFeed(ant); break;
//		case CommandType::FeedQueen: doAntFeedQueen(ant); break;
//		case CommandType::Defense: doAntDefence(ant); break;
//		case CommandType::CreateOfWorker: doAntCreateWorker(ant); break;
//		case CommandType::CreateOfSolder: doAntCreateSolder(ant); break;
        default: break;
    }

    ant.command().setCompleted(ant.interruptReason() & (Interrupt::CommandAborted | Interrupt::CommandCompleted));
}

bool Battle::commandIdle(Ant& ant)
{
    //LOGD("%s: command IDLE %i", ant.toString().c_str(), ant.command().m_value);

    if (ant.command().m_value >= 0)
    {
        --ant.command().m_value;
    }

    ant.setInterruptReason(Interrupt::CommandCompleted, ant.command().m_value <= 0);
    return true;
}

bool Battle::commandMove(Ant& ant)
{
    LOGD("%s: command MOVE %s", ant.toString().c_str(), ant.command().m_pos.toString().c_str());

    auto dist = moveAntToPoint(ant, ant.command().m_pos);

    if (dist < ant.command().m_lengthToPoint)
    {
        ant.command().m_lengthToPoint = dist;
        ant.command().m_abortingCount = 0;
    }
    else
    {
        ++ant.command().m_abortingCount;
    }

    ant.setInterruptReason(Interrupt::CommandAborted, dist < 0 || ant.command().m_abortingCount >= Constant::CommandAborting);
    ant.setInterruptReason(Interrupt::CommandCompleted, dist >= 0 && dist <= 1);

    return true;
}

bool Battle::commandAttack(Ant& ant)
{
    auto cmd = ant.command();

    LOGD("%s: command ATTACK %s", ant.toString().c_str(), ant.command().m_pos.toString().c_str());

    // Checking enemies in the range 1 cell
    std::vector<Ant*> enemies;
    auto player = ant.player();

    auto result = m_map->processingAntsInRadius(ant.position(), 1, [&enemies, player](Ant* cellAnt)
    {
        if (cellAnt->player()->index() != player->index())
        {
            enemies.push_back(cellAnt);
        }
    });

    if (enemies.size())
    {
        Ant* enemy = enemies[Math::random(0, enemies.size() - 1)];

        LOGD("%s dealt %i damage to %s", ant.toString().c_str(), ant.attack(), enemy->toString().c_str());

        if (!enemy->damage(ant))
        {
            m_map->forceCellChange(enemy->position());
            killAnt(*enemy);
        }

        m_map->forceCellChange(ant.position());
        m_logService->attack(ant, *enemy);
        return true;
    }

    // No enemies in range 1 cell, check range in the Constant::CommandRadius value
    size_t minDist = 0xffff;
    result = m_map->processingAntsInRadius(ant.position(), Constant::CommandRadius, [&enemies, &minDist, &ant](Ant* cellAnt)
    {
        if (cellAnt->player()->index() != ant.player()->index())
        {
            auto dist = Math::distanceTo(cellAnt->position(), ant.command().m_pos);
            if (dist < minDist)
            {
                enemies.clear();
                enemies.push_back(cellAnt);
                return;
            }
            if (dist == minDist)
            {
                enemies.push_back(cellAnt);
                return;
            }
            return;
        }
    });

    if (enemies.size())
    {
        Ant* enemy = enemies[Math::random(0, enemies.size() - 1)];
        auto dist = moveAntToPoint(ant, enemy->position());
        ant.setInterruptReason(Interrupt::CommandAborted, dist < 0);
    }

    ant.setInterruptReason(Interrupt::CommandCompleted, enemies.empty());
    return true;
}

//void Battle::commandAntExplore(AntSharedPtr& ant)
//{
//	std::shared_ptr<Player> player = ant->player().lock();
//	std::shared_ptr<Ant> queen = player->antQueen().lock();
//
//	Direction dirToQueen = Math::directionTo(ant->position(), queen->position());
//	Direction dirFromQueen =Math::inverseDirection(dirToQueen);
//	Direction dir = Math::probabilisticDirection(dirFromQueen);
//
//	moveAnt(ant, dir);
//
//	--ant->command().count;
//}

/*
bool Battle::commandMoveAndIdle(AntPtr ant)
{
    if (commandMove(ant))
    {
        ant->clearCommand();
        return true;
    }
    return false;
}

bool Battle::commandMoveAndAttack(AntPtr ant)
{
    if (commandMove(ant))
    {
        //ant->setCommand(CommandType::Attack, 0, 0);
        LOGD("The ant got the new command: Attack");
    }
    return false;
}
*/

/// \brief Moving the ant to the nearest food and do eating it
///
///
//void Battle::commandAntEat(AntSharedPtr& ant)
//{
//	Position foodPos = m_map->nearestFood(ant->position(), ant->maxVisibility());
//
//	if (!ant->isWorker()) {
//		//TODO fill LastCommand and AbortReason
//		ant->clearCommand();
//		return;
//	}
//
//	--ant->command().count;
//
//	if (Math::distanceTo(ant->position(), foodPos) > 1) {
//		moveAnt(ant, Math::directionTo(ant->position(), foodPos));
//		return;
//	}
//
//	auto cell = m_map->cell(foodPos).lock();
//	auto worker = dynamic_cast<AntWorker*>(ant.get());
//	int remainder = worker->modifyCargo(cell->food());
//	cell->setFood(remainder);
//
//	if (worker->isFullCargo()) {
//		//TODO fill LastCommand and AbortReason
//		ant->clearCommand();
//	}
//}


int16_t Battle::moveAntToPoint(Ant& ant, const Position& pos)
{
    auto dirToPoint = Math::directionTo(ant.position(), pos);
    auto dir = Math::probabilisticDirection(dirToPoint);
    auto oldPos = ant.position();

    LOGD("%s ---> %s: %s", ant.toString().c_str(), ant.command().m_pos.toString().c_str(), directionToString(dirToPoint, true).c_str());
    if (dirToPoint != dir)
    {
        LOGD("    dir %s changed to %s", directionToString(dirToPoint, true).c_str(), directionToString(dir, true).c_str());
    }

    auto result = moveAntToDirection(ant, dir);

    LOGD("    form %s moved to %s", oldPos.toString().c_str(), ant.position().toString().c_str());

    return result;
}

/// \brief Moving the ant to selected direction
///
/// If we can not move the ant to selected direction then we move ant to direction near to selected
int16_t Battle::moveAntToDirection(Ant& ant, const Direction& dir)
{
    // get odered directions
    std::vector<Direction> array_dir = Math::createDirectionArray(dir);

    for (auto& dir : array_dir)
    {
        // get the new position as the ant position and the direction
        Position newpos = ant.position() + Math::positionOffset(dir);

        // checking reachability of the new position
        if (m_map->isCellEmpty(newpos))
        {
            // if the cell is empty then move the ant to it
            m_map->moveAnt(ant, newpos);

            return Math::distanceTo(ant.position(), ant.command().m_pos);
        }

        // cell is not empty, go to next the direction and to check next
    }

    return -1;
}

bool Battle::killAnt(Ant& ant)
{
    LOGD("%s is died", ant.toString().c_str());

    auto player = ant.player();
    player->antIsDied(ant);
    m_map->removeAnt(ant.position());

    m_logService->antIsDied(ant);

    return true;
}

bool Battle::checkEndGame()
{
    size_t numberOfliving = 0;

    m_winner = nullptr;

    for (const auto& plr : m_players)
    {
        if (plr->antQueen()->status() != Ant::Status::Life)
        {
            removePlayerFromGame(*plr.get());
            continue;
        }

        m_winner = plr.get();
        ++numberOfliving;
    }

    return numberOfliving <= 1 ? true : false;
}

void Battle::removePlayerFromGame(Player& plr)
{
    for (auto& ant : m_ants)
    {
        if (ant->player()->index() == plr.index())
        {
            ant->kill(Ant::DeathReason::PlayerLoose);
            killAnt(*ant);
        }
    }

    m_logService->playerLost(plr);
    LOGD("'%s' #%i lost!", plr.teamName().c_str(), plr.index());
}

//void Battle::generateAntInfo(AntSharedPtr& ant, AntInfo& ai)
//{
//	auto visible = Math::visibleCells(ant->position(), ant->maxVisibility());
//	auto owner = ant->player().lock();
//	auto quuen = owner->antQueen().lock();
//	uint32_t min_dist_food = 0xffffffff;
//	uint32_t min_dist_enemy = 0xffffffff;
//
//	ai.healthPrecent = ant->healthPercent();
//	ai.satietyPrecent = ant->satietyPercent();
//	ai.cargo = ant->cargo();
////	ai.directionToQueen = Math::directionTo(ant->position(), quuen->position());
//	ai.distanceToQueen = Math::distanceTo(ant->position(), quuen->position());
//	ai.directionToLabel = Direction::Nord; //TODO fix it
//	ai.distanceToLabel = 0; //TODO fix it
//	ai.directionToNearEnemy = Direction::Nord;
//	ai.directionToNearFood = Direction::Nord;
//
//	for (auto& pos : visible) {
//		if (m_map->cell(pos).expired()) {
//			continue;
//		}
//
//		auto cell = m_map->cell(pos).lock();
//
//		if (cell->isEmpty() || cell->isStone()) {
//			continue;
//		} else if(cell->food()) {
//			uint32_t dist = Math::distanceTo(ant->position(), pos);
//
//			if (dist < min_dist_food) {
//				min_dist_food = dist;
//				ai.directionToNearFood = Math::directionTo(ant->position(), pos);
//			}
//
//			ai.countOfVisibleFood++;
//		} else {
//			auto cell_ant = cell->ant().lock();
//			auto cell_player = cell_ant->player().lock();
//
//			if (owner->index() == cell_player->index()) {
//				ai.countOfVisibleAlly++;
//			} else {
//				uint32_t dist = Math::distanceTo(ant->position(), pos);
//
//				if (dist < min_dist_enemy) {
//					min_dist_enemy = dist;
//					ai.directionToNearEnemy = Math::directionTo(ant->position(), pos);
//				}
//
//				ai.countOfVisibleEnemies++;
//			}
//		}
//	}
//}

};
