
#include "BattleLogService.h"

namespace WarAnts
{

void BattleLogService::add(const std::shared_ptr<IBattleLogProvider>& provider)
{
    for (auto& item : m_providers)
    {
        if (item.get() == provider.get())
        {
            return;
        }
    }

    m_providers.push_back(provider);
}

void BattleLogService::saveMapInfo(const Map& map)
{
    for (auto& provider : m_providers)
    {
        provider->saveMapInfo(map);
    }
}

void BattleLogService::savePlayer(const Player& player)
{
    for (auto& provider : m_providers)
    {
        provider->savePlayer(player);
    }
}

void BattleLogService::saveBeginTurn(uint32_t iteration)
{
    for (auto& provider : m_providers)
    {
        provider->saveBeginTurn(iteration);
    }
}

void BattleLogService::saveEndTurn(uint32_t iteration, size_t msec)
{
    for (auto& provider : m_providers)
    {
        provider->saveEndTurn(iteration, msec);
    }
}

void BattleLogService::saveMap(const Map& map)
{
    for (auto& provider : m_providers)
    {
        provider->saveMap(map);
    }
}

void BattleLogService::attack(const Ant& ant, const Ant& enemy)
{
    for (auto& provider : m_providers)
    {
        provider->attack(ant, enemy);
    }
}

void BattleLogService::antIsDied(const Ant& ant)
{
    for (auto& provider : m_providers)
    {
        provider->antIsDied(ant);
    }
}

void BattleLogService::playerLost(const Player& plr)
{
    for (auto& provider : m_providers)
    {
        provider->playerLost(plr);
    }
}

void BattleLogService::endGame(const Player* winner)
{
    for (auto& provider : m_providers)
    {
        provider->endGame(winner);
    }
}

};
