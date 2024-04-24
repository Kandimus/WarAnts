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
    void saveNewTurn(uint32_t iteration) override;
    void saveMap(const Map& map) override;

protected:
    std::vector<std::shared_ptr<IBattleLogProvider>> m_providers;
};

};
