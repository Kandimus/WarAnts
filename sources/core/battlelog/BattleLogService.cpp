
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

};
