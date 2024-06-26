#pragma once

#include <memory>
#include <vector>

#include "I_BattleLogProvider.h"

namespace WarAnts
{

class BattleLogService : public IBattleLogProvider
{
public:
    BattleLogService() = default;
    virtual ~BattleLogService() = default;

public:
    void add(const std::shared_ptr<IBattleLogProvider>& provider);

    void saveMapInfo(const Map& map) override;
    void savePlayer(const Player& player) override;
    void saveBeginTurn(uint32_t iteration) override;
    void saveEndTurn(uint32_t iteration, size_t msec) override;
    void saveMap(const Map& map) override;
    void attack(const Ant& ant, const Ant& enemy) override;
    void antIsDied(const Ant& ant) override;
    void playerLost(const Player& plr) override;
    void endGame(const Player* winner) override;

protected:
    std::vector<std::shared_ptr<IBattleLogProvider>> m_providers;
};

};
