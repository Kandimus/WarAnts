#include "TextScreenProvider.h"

#include <fstream>

#include "Log.h"
#include "../Map.h"
#include "../Cell.h"
#include "../Ant.h"
#include "../Player.h"

namespace WarAnts
{

TextScreenProvider::TextScreenProvider(const std::string& filename)
    : m_filename(filename)
{
    std::ofstream file(m_filename);

    if (!file.is_open())
    {
        if (!m_cantOpen)
        {
            LOGE("Error: Can create the '%s' log file!", m_filename.c_str());
            m_cantOpen = true;
        }
        return;
    }
}

bool TextScreenProvider::isFileOpen(std::ofstream& of)
{
    if (!of.is_open())
    {
        if (!m_cantOpen)
        {
            LOGE("Error: Can not open the '%s' log file!", m_filename.c_str());
            m_cantOpen = true;
        }
        return false;
    }

    m_cantOpen = false;
    return true;
}

void TextScreenProvider::saveMapInfo(const Map& map)
{
    if (!m_map.size())
    {
        m_w = map.size().x();
        m_h = map.size().y();
        m_map.resize(m_w * m_h);

        for (auto& item : m_map)
        {
            item = cEmpty;
        }
    }
}

void TextScreenProvider::savePlayer(const Player& player)
{

}

void TextScreenProvider::saveBeginTurn(uint32_t iteration)
{
}

void TextScreenProvider::saveEndTurn(uint32_t iteration, size_t msec)
{
}

void TextScreenProvider::saveMap(const Map& map)
{
    std::ofstream file(m_filename, std::ios::app);

    if (!isFileOpen(file))
    {
        return;
    }

    uint32_t size = map.size().x() * map.size().y();

    for (uint32_t ii = 0; ii < size; ++ii)
    {
        auto cell = map.cell(ii);

        if (!cell->isChanged())
        {
            continue;
        }

        if (cell->isEmpty())
        {
            m_map[ii] = cEmpty;
        }
        else if (cell->isStone())
        {
            m_map[ii] = cStone;
        }
        else if (cell->food())
        {
            m_map[ii] = cFood;
        }
        else
        {
            auto ant = cell->ant();
            auto player = ant->player();

            if (player->index() >= 4)
            {
                m_map[ii] = '@';
            }
            else
            {
                switch (ant->type())
                {
                    case AntType::Queen:  m_map[ii] = cQueen [player->index()]; break;
                    case AntType::Solder: m_map[ii] = cSolder[player->index()]; break;
                    case AntType::Worker: m_map[ii] = cWorker[player->index()]; break;
                    default: m_map[ii] = '?';
                }
            }
        }
    }

    file << '+';
    for (uint32_t x = 0; x < m_w; ++x)
    {
        file << '-';
    }
    file << '+' << std::endl;

    for (uint32_t y = 0; y < m_h; ++y)
    {
        file << '|';
        for (uint32_t x = 0; x < m_w; ++x)
        {
            file << m_map[x + y * m_w];
        }
        file << '|' << std::endl;
    }

    file << '+';
    for (uint32_t x = 0; x < m_w; ++x)
    {
        file << '-';
    }
    file << '+';

    file << std::endl;
    file << std::endl;

    file.close();
}

};
