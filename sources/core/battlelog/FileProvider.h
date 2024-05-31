#pragma once

#include <string>

#include "I_BattleLogProvider.h"

namespace WarAnts
{

class FileProvider : public IBattleLogProvider
{
public:
    FileProvider(const std::string& filename);
    virtual ~FileProvider() = default;

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
    bool isFileOpen(std::ofstream& of);

protected:
    std::string m_filename = "";
    bool m_cantOpen = false;
};

};
