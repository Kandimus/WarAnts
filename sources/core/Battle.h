#pragma once

#include <stdint.h>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include "Direction.h"

namespace WarAnts
{

class Ant;
class BattleLogService;
class Config;
class Map;
class Player;

using AntPtr = std::shared_ptr<Ant>;
using ListAnts = std::list<AntPtr>;
using PlayerPtr = std::shared_ptr<Player>;

class Battle
{
public:
    Battle(const std::string& confname, const std::vector<std::string>& players);
    virtual ~Battle() = default;

    int run();

protected:
    //std::vector<std::weak_ptr<Ant>> sortAnts();

    void doAntCommand(AntPtr ant);
    bool commandMove(AntPtr ant);
    bool commandAttack(AntPtr ant);
    bool commandMoveAndIdle(AntPtr ant);
    bool commandMoveAndAttack(AntPtr ant);
    
    //void commandAntEat(AntSharedPtr& ant);

    bool moveAnt(AntPtr ant, const Direction& dir);
    bool killAnt(AntPtr ant);

    //void generateAntInfo(AntSharedPtr& ant, AntInfo& ai);

protected:
    uint32_t m_iteration = 0;
    bool m_isInit = false;
    uint64_t m_uid; //Battle UID
    std::shared_ptr<Config> m_conf;
    std::shared_ptr<Map> m_map;

    std::vector<PlayerPtr> m_players;
    ListAnts m_ants;

    std::shared_ptr<BattleLogService> m_logService;
};

};
