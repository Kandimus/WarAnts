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
class Position;

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
    std::string createUBID() const;
    //std::vector<std::weak_ptr<Ant>> sortAnts();

    void processingInterrupt(Ant& ant);

    void doAntCommand(Ant& ant);
    bool commandIdle(Ant& ant);
    bool commandMove(Ant& ant);
    bool commandAttack(Ant& ant);
    bool commandMoveAndIdle(AntPtr ant);
    bool commandMoveAndAttack(AntPtr ant);
    
    //void commandAntEat(AntSharedPtr& ant);

    int16_t moveAntToPoint(Ant& ant, const Position& pos);
    int16_t moveAntToDirection(Ant& ant, const Direction& dir);
    bool killAnt(Ant& ant);

    //void generateAntInfo(AntSharedPtr& ant, AntInfo& ai);

protected:
    uint32_t m_iteration = 0;
    bool m_isInit = false;
    std::shared_ptr<Config> m_conf;
    std::shared_ptr<Map> m_map;

    std::vector<PlayerPtr> m_players;
    ListAnts m_ants;

    std::shared_ptr<BattleLogService> m_logService;
};

};
