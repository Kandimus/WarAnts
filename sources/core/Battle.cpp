#include "Battle.h"

#include "Log.h"

#include "AntFabric.h"
#include "constants.h"
#include "Cell.h"
#include "Config.h"
#include "Map.h"
#include "MapMath.h"
#include "Player.h"
#include "vectorMin.h"
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

    // init the ant fabric
    AntFabric::init(m_conf->antsFileSettings());

    // create the players list
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

        // Remove dead ants from game (map)
        for (auto iter = m_ants.begin(); iter != m_ants.end(); )
        {
            if ((*iter)->status() == Ant::Status::Dead)
            {
                m_deadAnts.push_back(*iter);
                iter = m_ants.erase(iter);
            }
            else
            {
                ++iter;
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
        auto result = m_map->processingAntsInRadius(ant.position(), ant.visibility() / Constant::DivCloseRadius,
            [&enemyIsPresent, player](Ant* cellAnt)
            {
                enemyIsPresent = cellAnt->player()->index() != player->index();
            });
        ant.setInterruptReason(Interrupt::CloseEnemy, enemyIsPresent);
    }

    if (ant.interruptFlags() & Interrupt::FarEnemy)
    {
        bool enemyIsPresent = false;
        auto player = ant.player();
        auto result = m_map->processingAntsInRadius(ant.position(), ant.visibility() / Constant::DivFarRadius,
            [&enemyIsPresent, player](Ant* cellAnt)
            {
                enemyIsPresent = cellAnt->player()->index() != player->index();
            });
        ant.setInterruptReason(Interrupt::FarEnemy, enemyIsPresent);
    }

    if (ant.interruptFlags() & Interrupt::CloseFood)
    {
        bool foodIsPresent = false;
        auto result = m_map->processingRadius(ant.position(), ant.visibility() / Constant::DivCloseRadius,
            [&foodIsPresent](const Cell& cell)
            {
                foodIsPresent |= !!cell.food();
            });
        ant.setInterruptReason(Interrupt::CloseFood, foodIsPresent);
    }

    if (ant.interruptFlags() & Interrupt::FarFood)
    {
        bool foodIsPresent = false;
        auto result = m_map->processingRadius(ant.position(), ant.visibility() / Constant::DivFarRadius,
            [&foodIsPresent](const Cell& cell)
            {
                foodIsPresent |= !!cell.food();
            });
        ant.setInterruptReason(Interrupt::FarFood, foodIsPresent);
    }

    // Queen has been attacked!
    ant.setInterruptReason(Interrupt::QueenUnderAttack,
        ant.player()->antQueen()->isUnderAttack() && (ant.interruptFlags() & Interrupt::QueenUnderAttack));

    if (ant.interruptReason())
    {
        LOGD("%s have intrrupt 0x%04x", ant.toString().c_str(), ant.interruptReason());
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
        case Command::Feed: commandFoodCellOperation(ant, true); break;
        case Command::TakeFood: commandFoodCellOperation(ant, false); break;
        case Command::Eat: commandEatFromCargo(ant); break;
        case Command::Cater: commandCater(ant);break;
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
    auto& cmd = ant.command();

    LOGD("%s: command MOVE %s, value %i", ant.toString().c_str(), cmd.m_pos.toString().c_str(), cmd.m_value);

    --cmd.m_value;
    auto dist = moveAntToPoint(ant, cmd.m_pos);

    ant.setInterruptReason(Interrupt::CommandAborted, dist < 0 || cmd.m_value <= 0);
    ant.setInterruptReason(Interrupt::CommandCompleted, dist == 0 || dist == 1);

    if (ant.interruptReason() | Interrupt::CommandCompleted)
    {
        LOGD("%s: command MOVE has been finished with the value %i", ant.toString().c_str(), ant.command().m_value);
    }

    return true;
}

//TODO На переделку!!!!!!!!!
bool Battle::commandAttack(Ant& ant)
{
    auto cmd = ant.command();

    LOGD("%s: command ATTACK %s", ant.toString().c_str(), ant.command().m_pos.toString().c_str());

    // Checking enemies in the range 1 cell
    vectorMin<Ant*> enemies;
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
        Ant* enemy = enemies.randomIndex();

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

    // No enemies in range 1 cell, check within the Constant::CommandRadius radius of the command point
    result = m_map->processingAntsInRadius(cmd.m_pos, Constant::CommandRadius, [&enemies, &ant](Ant* cellAnt)
    {
        if (cellAnt->player()->index() != ant.player()->index())
        {
            enemies.add(cellAnt, Math::distanceTo(cellAnt->position(), ant.position()));
        }
    });

    if (enemies.size())
    {
        Ant* enemy = enemies.randomIndex();
        auto dist = moveAntToPoint(ant, enemy->position());
        ant.setInterruptReason(Interrupt::CommandAborted, dist < 0);
    }

    ant.setInterruptReason(Interrupt::CommandCompleted, enemies.empty());
    return true;
}

//TODO На переделку!!!!!!!!!
bool Battle::commandFoodCellOperation(Ant& ant, bool isFeed)
{
    auto cmd = ant.command();

    LOGD("%s: command %s %s", ant.toString().c_str(),
        isFeed ? "FEED" : "TAKE FOOD", cmd.m_pos.toString().c_str());

    if (ant.isQueen())
    {
        LOGE("%s: is a queen! Command aborted", ant.toString().c_str());
        ant.setInterruptReason(Interrupt::CommandAborted, true);
        return false;
    }

    // Checking food in the range 1 cell
    vectorMin<Position> foods;

    auto result = m_map->processingRadius(ant.position(), 1, [&foods](const Cell& cell)
    {
        if (cell.food())
        {
            foods.push_back(cell.position());
        }
    });

    if (foods.size())
    {
        Position foodPos = foods.randomIndex();

        // check for the user set position 
        for (const auto& pos: foods)
        {
            if (pos == cmd.m_pos)
            {
                foodPos = pos;
            }
        }

        LOGD("%s take the food on %s", ant.toString().c_str(), foodPos.toString().c_str());

        int16_t food = m_map->takeFood(foodPos, ant, !isFeed);
        if (food <= 0)
        {
            LOGE("%s cannot take the food at %s", ant.toString().c_str(), foodPos.toString().c_str());
            ant.setInterruptReason(Interrupt::CommandAborted, true);
            return false;
        }
        LOGD("The remain of the food cell is %i", m_map->cell(foodPos)->food());

        if (isFeed)
        {
            ant.eat(food);
            ant.setInterruptReason(Interrupt::CommandCompleted, ant.satiety() >= ant.maxSatiety());
            LOGD("%s eats %i of food. The Satiety is %.2f now", ant.toString().c_str(), food, ant.satietyPercent());
        }
        else
        {
            ant.modifyCargo(food);
            ant.setInterruptReason(Interrupt::CommandCompleted, ant.cargo() >= ant.maxCargo());
            LOGD("%s free cargo %.2f", ant.toString().c_str(), 100.f - ant.cargoPercent());
        }

        return true;
    }

    // No foods in range 1 cell, check range in the Constant::CommandRadius value
    result = m_map->processingRadius(cmd.m_pos, Constant::CommandRadius, [&foods, &ant](const Cell& cell)
    {
        if (cell.food())
        {
            foods.add(cell.position(), Math::distanceTo(cell.position(), ant.position()));
        }
    });

    if (foods.size())
    {
        Position foodPos = foods.randomIndex();
        auto dist = moveAntToPoint(ant, foodPos);
        ant.setInterruptReason(Interrupt::CommandAborted, dist < 0);
    }

    ant.setInterruptReason(Interrupt::CommandCompleted, foods.empty());
    return true;
}

// Из карго могут кушать только рабочий муравей и королева
bool Battle::commandEatFromCargo(Ant& ant)
{
    auto cmd = ant.command();

    LOGD("%s: command EAT", ant.toString().c_str());

    if (ant.isSolder())
    {
        LOGE("%s: is a solder! Command aborted", ant.toString().c_str());
        ant.setInterruptReason(Interrupt::CommandAborted, true);
        return true;
    }

    int16_t food = ant.eatFromCargo();

    LOGD("%s: eatted % of food, satiety: %i, cargo: %i", ant.toString().c_str(),
        food, ant.satiety(), ant.cargo());

    ant.setInterruptReason(Interrupt::CommandCompleted, food <= 0);
    ant.setInterruptReason(Interrupt::CommandAborted, food < 0);

    return true;
}

bool Battle::commandCater(Ant& ant)
{
    LOGD("%s: command CATER %s, target %s",
        ant.toString().c_str(), ant.command().m_pos,
        ant.command().target() ? ant.command().target()->toString().c_str() : "null");
    
    if (!ant.isWorker())
    {
        LOGE("%s: is not a worker! Command aborted", ant.toString().c_str());
        ant.setInterruptReason(Interrupt::CommandAborted, true);
        return true;
    }

    if (!ant.cargo())
    {
        LOGD("    The empty cargo! command aborted!");
        ant.setInterruptReason(Interrupt::CommandCompleted, true);
        return true;
    }
    
    auto& cmd = ant.command();
    
    // if ant did not reach the target point
    int16_t dist = Math::distanceTo(ant.position(), cmd.m_pos);
    if (dist > Constant::CommandRadius)
    {
        auto dist = moveAntToPoint(ant, cmd.m_pos);
        --cmd.m_value;
        ant.setInterruptReason(Interrupt::CommandAborted, dist < 0 || cmd.m_value <= 0);
        return true;
    }
    
    // Now the ant is in the command's radius

    // check target on radius
    if (cmd.target())
    {
        if (Math::distanceTo(cmd.m_pos, cmd.target()->position()) > Constant::CommandRadius ||
            cmd.target()->status() == Ant::Status::Dead)
        {
            // The ant is lost the target because the target leave out from the command's radius
            cmd.setTarget(nullptr);
        }
    }

    // Find a new target. Hint - it is a closest ant :)
    if (!cmd.target())
    {
        vectorMin<Ant*> allies;
        auto result = m_map->processingAntsInRadius(cmd.m_pos, Constant::CommandRadius, [&allies, &ant](Ant* cellAnt)
        {
            if (cellAnt->player()->index() == ant.player()->index() &&
                cellAnt->id() != ant.id() &&
                cellAnt->status() != Ant::Status::Dead)
            {
                allies.add(cellAnt, Math::distanceTo(cellAnt->position(), ant.position()));
            }
        });

        if (allies.empty())
        {
            ant.setInterruptReason(Interrupt::CommandAborted, true);
            return true;
        }

        cmd.setTarget(allies.randomIndex());
    }

    // The ant have the target
    dist = Math::distanceTo(ant.position(), cmd.target()->position());
    if (dist <= 1)
    {
        ant.cater(*cmd.target());
        ant.setInterruptReason(Interrupt::CommandCompleted, !ant.cargo() || cmd.target()->satietyPercent() >= 100.0f);
    }
    else
    {
        dist = moveAntToPoint(ant, cmd.target()->position());
        ant.setInterruptReason(Interrupt::CommandAborted, dist < 0);
    }

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

} //namespace WarAnts
