#pragma once

#include <vector>
#include <string>

#include "I_BattleLogProvider.h"

namespace WarAnts
{

class TextScreenProvider : public IBattleLogProvider
{
public:
    TextScreenProvider(const std::string& filename);
    virtual ~TextScreenProvider() = default;

    void saveMapInfo(const Map& map) override;
    void savePlayer(const Player& player) override;
    void saveBeginTurn(uint32_t iteration) override;
    void saveEndTurn(uint32_t iteration, size_t msec) override;
    void saveMap(const Map& map) override;

protected:
    bool isFileOpen(std::ofstream& of);

protected:
    std::string m_filename = "";
    bool m_cantOpen = false;

    uint32_t m_w = 0;
    uint32_t m_h = 0;
    std::vector<char> m_map;
    uint32_t m_iteration = 0;

    const char cEmpty = ' ';
    const char cStone = '#';
    const char cFood  = '$';
    const char cQueen[4]  = {'q', 'w', 'e', 'r'};
    const char cSolder[4] = {'a', 's', 'd', 'f'};
    const char cWorker[4] = {'z', 'x', 'c', 'v'};
};

};
