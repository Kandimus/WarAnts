#pragma once

#include <stdint.h>
#include <memory>
#include <vector>
#include <list>

#include "Ant.h"
#include "MapMath.h"

namespace WarAnts
{

class Cell;
class Config;
class Player;

using PlayerPtr = std::shared_ptr<Player>;

class Map
{
public:
    Map(const std::shared_ptr<Config>& conf, const std::string& filename);
    virtual ~Map() = default;

    inline std::shared_ptr<Config> config() const { return m_conf; }

    inline const Cell* cell(Position pos) const
    {
        uint32_t idx = absPosition(pos);
        return (idx < m_map.size()) ? m_map[idx].get() : nullptr;
    }
    inline const Cell* cell(uint32_t x, uint32_t y) const
    {
        return cell(Position(x, y));
    }
    inline const Cell* cell(uint32_t offset) const
    {
        return (offset < m_map.size()) ? m_map[offset].get() : nullptr;
    }

    inline const Position& size() const { return m_size; }
    inline uint16_t sizeX() const { return m_size.x(); }
    inline uint16_t sizeY() const { return m_size.y(); }

    ListAnts generate(const std::vector<std::shared_ptr<Player>>& players);

    inline bool isValidPosition(const Position& pos) const
    {
        return pos.x() >= 0 && pos.x() < m_size.x() && pos.y() >= 0 && pos.y() < m_size.y();
    }

    inline bool isCellEmpty(int32_t x, int32_t y) const { return isCellEmpty(Position(x, y)); }
    bool isCellEmpty(const Position& pos) const;
    void clearChanged();
    void forceCellChange(const Position& pos);

    Position closestAvaliblePosition(const Position& pos) const;
    
    int16_t takeFood(const Position& pos, Ant& ant, bool checkCargo);

    void moveAnt(Ant& ant, const Position& pos);
    void removeAnt(const Position& pos);
    AntPtr createAnt(const PlayerPtr& player, Ant::Type antType, const Position& pos, uint16_t r);
    
    template<typename F>
    bool processingRadius(const Position& pos, int16_t radius, const F& f)
    {
        auto listPos = Math::visibleCells(pos, radius);
        if (listPos.empty())
        {
            return false;
        }
        
        for (auto& pos : listPos)
        {
            auto pCell = cell(pos);
            if (!pCell)
            {
                continue;
            }
            f(*pCell);
        }
        return true;
    }

    template<typename F>
    bool processingAntsInRadius(const Position& pos, int16_t radius, const F& f)
    {
        auto listPos = Math::visibleCells(pos, radius);
        if (listPos.empty())
        {
            return false;
        }

        for (auto& pos : listPos)
        {
            auto pCell = cell(pos);
            if (!pCell)
            {
                continue;
            }

            if (pCell->ant())
            {
                f(pCell->ant());
            }
        }
        return true;
    }

protected:
    void setSize(int16_t w, int16_t h);
    void createMap();
    bool load(std::vector<Position>& start);
    void incPosition(Position& pos, uint32_t x = 1) const;
    int32_t absPosition(const Position& pos) const;

protected:
    Position m_size;
    std::vector<std::shared_ptr<Cell>> m_map;
    std::shared_ptr<Config> m_conf;
    std::string m_filename;

    const uint16_t m_startingSquare = 10;
    const uint16_t m_minWidth = 10;
    const uint16_t m_minHeight = 10;
};

};
