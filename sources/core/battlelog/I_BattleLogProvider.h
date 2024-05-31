#pragma once

#include <memory>

namespace WarAnts
{

class Ant;
class Player;
class Map;

class IBattleLogProvider
{
public:
    IBattleLogProvider() = default;
    virtual ~IBattleLogProvider() = default;

//	virtual void saveBattle(const std::weak_ptr<Map>& map) = 0;
    virtual void saveMapInfo(const Map& map) = 0;
    virtual void savePlayer(const Player& player) = 0;
    virtual void saveBeginTurn(uint32_t iteration) = 0;
    virtual void saveEndTurn(uint32_t iteration, size_t msec) = 0;
    virtual void saveMap(const Map& map) = 0;
    virtual void attack(const Ant& ant, const Ant& enemy) = 0;
    virtual void antIsDied(const Ant& ant) = 0;
    virtual void playerLost(const Player& plr) = 0;
    virtual void endGame(const Player* winner) = 0;
//	virtual void saveFinal(const std::weak_ptr<Map>& map) = 0;
};

};
