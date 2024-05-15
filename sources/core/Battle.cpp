#include "Battle.h"

#include "Log.h"

#include "AntFabric.h"
#include "Cell.h"
#include "Config.h"
#include "Map.h"
#include "MapMath.h"
#include "Player.h"
#include "VirtualMachine.h"

#include "battlelog/BattleLogService.h"
#include "battlelog/FileProvider.h"
#include "battlelog/TextScreenProvider.h"

//std::string AntInfoToString(const AntInfo& ai)
//{
//	nlohmann::json json;
//
//	json["iteration"] = ai.iteration;
//	json["countOfWorker"] = ai.countOfWorker;
//	json["countOfSolder"] = ai.countOfSolder;
//	json["countOfFood"] = ai.countOfFood;
//	json["healthPrecent"] = ai.healthPrecent;
//	json["satietyPrecent"] = ai.satietyPrecent;
//	json["cargo"] = ai.cargo;
//	json["distanceToQueen"] = ai.distanceToQueen;
//	json["directionToLabel"] = Math::descriptionDirection(ai.directionToLabel);
//	json["distanceToLabel"] = ai.distanceToLabel;
//	json["countOfVisibleAlly"] = ai.countOfVisibleAlly;
//	json["countOfVisibleEnemies"] = ai.countOfVisibleEnemies;
//	json["countOfVisibleFood"] = ai.countOfVisibleFood;
//	json["directionToNearEnemy"] = Math::descriptionDirection(ai.directionToNearEnemy);
//	json["directionToNearFood"] = Math::descriptionDirection(ai.directionToNearFood);
//
//	return nlohmann::to_string(json);
//}

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

            if(!ant->hasCommand())
            {
                VirtualMachine vm(m_map, ant);

                vm.run();
            //	AntInfo ai;
            //	Command cmd;

            //	auto queen = player->antQueen().lock();

            //	generateAntInfo(ant, ai);
            //	ai.iteration = m_iteration;
            //	ai.countOfWorker = player->countOfWorkers();
            //	ai.countOfSolder = player->countOfSolders();
            //	ai.countOfFood = queen->cargo();

            //	if (Log::instance().level() >= Log::Level::Debug) {
            //		Log::instance().put(Log::Level::Debug, "AntInfo = " + AntInfoToString(ai));
            //	}

            //	ant->process(ai, cmd);
            //	ant->setCommand(cmd);
            }

            doAntCommand(ant);
            m_map->forceCellChange(ant->position());

            // Ant has been died
            if (!ant->endTurn())
            {
                killAnt(ant);
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


void Battle::doAntCommand(AntPtr ant)
{
    auto cmd = ant->command();

    switch(cmd.m_type)
    {
        case CommandType::Idle: break;
        case CommandType::Move: commandMove(ant); break;
        case CommandType::Attack: commandAttack(ant); break;
        case CommandType::MoveAndIdle: commandMoveAndIdle(ant); break;
        case CommandType::MoveAndAttack: commandMoveAndAttack(ant);break;
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

    //if (!cmd.count)
    //{
    //    ant->clearCommand();
    //}
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

bool Battle::commandMove(AntPtr ant)
{
    auto dirToPoint = Math::directionTo(ant->position(), ant->command().m_pos);
    auto dir = Math::probabilisticDirection(dirToPoint);

    auto oldPos = ant->position();
    LOGD("ant %s ---> %s: %s", ant->position().toString().c_str(), ant->command().m_pos.toString().c_str(), directionToString(dirToPoint, true).c_str());
    LOGD("dir %s changed to %s", directionToString(dirToPoint, true).c_str(), directionToString(dir, true).c_str());
    LOGD("ant %s move to %s: %s", oldPos.toString().c_str(), ant->position().toString().c_str());

    return moveAnt(ant, dir);
}

bool Battle::commandAttack(AntPtr ant)
{
    auto arrayOfEnemy = m_map->nearestEnemies(ant->position(), 1);

    if (arrayOfEnemy.empty())
    {
        ant->clearCommand();
        return true;
    }

    int index = (int)Math::random(0, arrayOfEnemy.size() - 1);
    auto enemy = arrayOfEnemy[index];

    //TODO Нужно ли тут проверять, что атакуемый муравей умер? и соответственно вызывать player->antIsDied()
    //     или же дать муравью ответить на удар или другое действие и убить его в его фазу хода?
    if (!enemy->damage(ant->attack()))
    {
        killAnt(enemy);
    }

    return false;
}

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
        int16_t userdata = ant->command().m_userData;
        ant->clearCommand();
        ant->setCommand(CommandType::Attack, 0, 0, userdata);
        LOGD("ant new command Attack");
    }
    return false;
}

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


/// \brief Moving the ant to selected direction
///
/// If we can not move the ant to selected direction then we move ant to direction near to selected
bool Battle::moveAnt(AntPtr ant, const Direction& dir)
{
    // get odered directions
    std::vector<Direction> array_dir = Math::createDirectionArray(dir);

    for (auto& dir : array_dir)
    {
        // get the new position as the ant position and the direction
        Position newpos = ant->position() + Math::positionOffset(dir);

        // checking reachability of the new position
        if (m_map->isCellEmpty(newpos))
        {
            // if the cell is empty then move the ant to it
            m_map->moveAnt(ant, newpos);

            return Math::distanceTo(ant->position(), ant->command().m_pos) <= 1;
        }

        // cell is not empty, go to next the direction and to check next
    }

    //TODO Set the lastCommand as the current command, set reason of abortion of command and do cancel of the current command
    //ant->clearCommand();
    return true;
}

bool Battle::killAnt(AntPtr ant)
{
    auto player = ant->player();
    player->antIsDied(ant);

    m_map->removeAnt(ant->position());

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
