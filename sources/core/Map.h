#pragma once

#include <stdint.h>
#include <memory>
#include <vector>
#include <list>

#include "Ant.h"

namespace WarAnts
{

class Cell;
class Config;
class Player;

class Map
{
public:
    Map(const std::shared_ptr<Config>& conf);
    virtual ~Map() = default;

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
    inline uint32_t sizeX() const { return m_size.x(); }
    inline uint32_t sizeY() const { return m_size.y(); }

    ListAnts generate(const std::vector<std::shared_ptr<Player>>& players);

    bool isCellEmpty(const Position& pos) const;
    bool isCellEmpty(int32_t x, int32_t y) const;
    void clearChanged();

    Position nearAvaliblePosition(const Position& pos) const;
    Position nearestFood(const Position& pos, uint32_t visible) const;

    void moveAnt(const std::shared_ptr<Ant>& ant, const Position& pos);
    void removeAnt(const Position& pos);
    std::shared_ptr<Ant> createAnt(std::shared_ptr<Player> player, AntType antType, const Position& pos, uint16_t r);

protected:
    void createMap(uint32_t w, uint32_t h);
    void incPosition(Position& pos, uint32_t x = 1) const;
    inline int32_t absPosition(const Position& pos) const { return pos.x() + pos.y() * m_size.x(); }

protected:
    Position m_size;
    std::vector<std::shared_ptr<Cell>> m_map;
    std::shared_ptr<Config> m_conf;

    const uint32_t m_startingSquare = 10;
    const uint32_t m_minWidth = 10;
    const uint32_t m_minHeight = 10;
};

};
