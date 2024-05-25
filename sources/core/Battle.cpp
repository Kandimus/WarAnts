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

Battle::Battle(const std::string& confname, const std::vector<std::string>& players)
{
    m_conf = std::make_shared<Config>(confname);
    m_map  = std::make_shared<Map>(m_conf);

    // init ant fabric
    AntFabric::init(m_conf->antsFileSettings());

    // create the player list
    uint32_t player_index = 0;
    for (auto& libname : players)
    {
        m_players.push_back(std::make_shared<Player>(player_index++, "players/" + libname));
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

    // Generate UBID
    m_conf->setUBID(createUBID());

    m_logService = std::make_shared<BattleLogService>();
    m_logService->add(std::make_shared<FileProvider>("test_battle.json"));
    m_logService->add(std::make_shared<TextScreenProvider>("test_battle_screen.txt"));

    LOGI("create new battle. map is [%i x %i]", m_conf->width(), m_conf->height());

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

    //TODO create UID of battle

    // create list of all ant
    m_ants = m_map->generate(m_players);

    //TEST!!!
    //m_ants.begin()->get()->setCommand(CommandType::MoveAndIdle, 1, 1, 0);

    // send of starting info
    m_logService->saveMapInfo(*m_map.get());
    for (auto& player : m_players)
    {
        m_logService->savePlayer(*player.get());
    }
    m_logService->saveMap(*m_map.get());

    // main loop
    while(true)
    {
        //---------------------------------------------------------------------
        // Start of iteration
        auto timeStart = getTickCount();

        // clear IsChange flag
        m_map->clearChanged();
        m_iteration++;

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
            if (ant->status() == AntStatus::Dead)
            {
                continue;
            }

            ant->beginTurn();

            processingInterrupt(*ant);

            if(ant->interruptReason())
            {
                VirtualMachine vm(m_map, ant);
                vm.run();
            }

            doAntCommand(*ant);
            m_map->forceCellChange(ant->position());

            // Ant has been died
            if (!ant->endTurn())
            {
                killAnt(*ant.get());
            }
        }

        // delete dead ants
        for (auto pAnt = m_ants.begin(); pAnt != m_ants.end(); )
        {
            if ((*pAnt)->status() == AntStatus::Dead)
            {
                pAnt = m_ants.erase(pAnt);
            }
            else
            {
                ++pAnt;
            }
        }

        //---------------------------------------------------------------------
        // End of iteration
        m_logService->saveMap(*m_map.get());

        //TODO check for end of game
        //if (m_iteration > 3) break;

        m_logService->saveEndTurn(m_iteration, getTickCount() - timeStart);

        if (m_ants.empty())
        {
            break;
        }
    }

    return 0;
}

void Battle::processingInterrupt(Ant& ant)
{
    if (ant.interruptFlags() & Interrupt::CloseEnemy)
    {
    }

    if (ant.interruptFlags() & Interrupt::FarEnemy)
    {

    }

    if (ant.interruptFlags() & Interrupt::CloseFood)
    {
    }

    if (ant.interruptFlags() & Interrupt::FarFood)
    {

    }

    // Queen
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
    if (ant.command().m_value >= 0)
    {
        --ant.command().m_value;
    }

    ant.setInterruptReason(Interrupt::CommandCompleted, ant.command().m_value <= 0);
    return true;
}

bool Battle::commandMove(Ant& ant)
{
    auto dist = moveAntToPoint(ant, ant.command().m_pos);

    ant.setInterruptReason(Interrupt::CommandAborted, dist < 0);
    ant.setInterruptReason(Interrupt::CommandCompleted, dist >= 0 || dist <= 1);

    return true;
}

bool Battle::commandAttack(Ant& ant)
{
    auto cmd = ant.command();

    switch(cmd.m_value)
    {
        case Command::StageMovingToPoint:
        {
            auto dist = moveAntToPoint(ant, ant.command().m_pos);
            ant.setInterruptReason(Interrupt::CommandAborted, dist < 0);
            cmd.m_value = (dist >= 0 || dist <= 1) ? Command::StageMovingToAttack : cmd.m_value;
        }
        break;

        case Command::StageMovingToAttack:
        {
            Ant* enemy = nullptr;
            uint32_t minDist = 0xffffffff;

            auto result = m_map->processingRadius(ant.command().m_pos, Constant::CommandRadius, [&enemy, &minDist, &ant](const Cell* cell)
                {
                    auto cellAnt = cell->ant();
                    if (!cellAnt)
                    {
                        return;
                    }

                    if (cellAnt->player() != ant.player())
                    {
                        auto dist = Math::distanceTo(ant.position(), cellAnt->position());
                        if (dist < minDist)
                        {
                            minDist = dist;
                            enemy = cellAnt;
                        }
                    }
                });
            
            if (!result)
            {
                ant.setInterruptReason(Interrupt::CommandAborted, true);
                return true;
            }

            if (minDist == 1)
            {
                if (!enemy->damage(ant.attack()))
                {
                    killAnt(*enemy);
                }
            }
            else
            {
                auto dist = moveAntToPoint(ant, enemy->position());
                ant.setInterruptReason(Interrupt::CommandAborted, dist < 0);
            }
        }
        break;
    }

/*
    auto arrayOfEnemy = m_map->nearestEnemies(ant.position(), 1);

    if (arrayOfEnemy.empty())
    {
        ant.clearCommand();
        return true;
    }

    int index = (int)Math::random(0, arrayOfEnemy.size() - 1);
    auto enemy = arrayOfEnemy[index];

    //TODO Нужно ли тут проверять, что атакуемый муравей умер? и соответственно вызывать player->antIsDied()
    //     или же дать муравью ответить на удар или другое действие и убить его в его фазу хода?
    if (!enemy->damage(ant.attack()))
    {
        killAnt(enemy);
    }
*/
    return false;
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
    LOGD("ant %s ---> %s: %s", ant.position().toString().c_str(), ant.command().m_pos.toString().c_str(), directionToString(dirToPoint, true).c_str());
    LOGD("dir %s changed to %s", directionToString(dirToPoint, true).c_str(), directionToString(dir, true).c_str());
    LOGD("ant %s move to %s: %s", oldPos.toString().c_str(), ant.position().toString().c_str());

    return moveAntToDirection(ant, dir);
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
    auto player = ant.player();
    player->antIsDied(ant);
    m_map->removeAnt(ant.position());

    return true;
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
