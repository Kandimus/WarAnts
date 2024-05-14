#include "Map.h"

#include <vector>
#include "Log.h"

#include "AntFabric.h"
#include "Cell.h"
#include "Config.h"
#include "Direction.h"
#include "Math.h"
#include "Player.h"
#include "MapMath.h"

namespace WarAnts
{

Map::Map(const std::shared_ptr<Config>& conf)
{
    m_conf = conf;

    uint32_t w = m_conf->width();
    uint32_t h = m_conf->height();

    if (w < m_minWidth)
    {
        w = m_minWidth;
        LOGI("Set width = %i", w);
    }

    if (h < m_minHeight)
    {
        h = m_minHeight;
        LOGI("Set height = %i", h);
    }

    createMap(w, h);

    LOGI("Create map [%i x %i]", m_size.x(), m_size.y());
}

ListAnts Map::generate(const std::vector<std::shared_ptr<Player>>& players)
{
    ListAnts ants;

    // countCell = m_map.size();

    //TODO generate stone

    //TODO generate food

    //TODO generate ants
    for (auto& player : players)
    {
        Position posQueen(static_cast<uint16_t>(Math::random(0, m_size.x())),
                          static_cast<uint16_t>(Math::random(0, m_size.y())));

        posQueen = nearAvaliblePosition(posQueen);
        LOGD("Queen #%i [%i x %i]", player->index(), posQueen.x(), posQueen.y());

        // do place Queen
        auto queen = createAnt(player, AntType::Queen, posQueen, 1);
        ants.push_back(queen);

        // do place workers
        for (uint32_t ii = 0; ii < m_conf->workerCountOfStart(); ++ii)
        {
            auto worker = createAnt(player, AntType::Worker, posQueen, m_startingSquare);
            ants.push_back(worker);
        }

        // do place solders
        for (uint32_t ii = 0; ii < m_conf->solderCountOfStart(); ++ii)
        {
            auto solder = createAnt(player, AntType::Solder, posQueen, m_startingSquare);
            ants.push_back(solder);
        }
    }

    return ants;
}

AntPtr Map::createAnt(const PlayerPtr& player, AntType antType, const Position& pos, uint16_t r)
{
    Position calc_pos(static_cast<uint16_t>(Math::random(0, r * 2)), static_cast<uint16_t>(Math::random(0, r * 2)));
    calc_pos -= r;
    calc_pos += pos;
    calc_pos = nearAvaliblePosition(calc_pos);

    auto ant = AntFabric::createAnt(player, antType);

    ant->setPosition(calc_pos);
    ant->reset();

    m_map[absPosition(calc_pos)]->setAnt(ant);

    return ant;
}

void Map::removeAnt(const Position& pos)
{
    m_map[absPosition(pos)]->removeAnt();
    //TODO Perhaps in the place of a dead ant you can create food
}

bool Map::isCellEmpty(const Position& pos) const
{
    int32_t idx = -1;

    if (m_conf->isBordered())
    {
        if (0 > pos.x() || pos.x() >= m_size.x() ||
            0 > pos.y() || pos.y() >= m_size.y())
        {
            return false;
        }
        idx = absPosition(pos);
    }
    else
    {
        Position newPos = pos;
        newPos.setX(pos.x() % m_size.x());
        newPos.setY(pos.y() % m_size.y());

        idx = absPosition(newPos);
    }

    return m_map[idx]->isEmpty();
}

void Map::clearChanged()
{
    for (auto& cell : m_map)
    {
        cell->clearChanged();
    }
}

void Map::forceCellChange(const Position& pos)
{
    if (isValidPosition(pos))
    {
        m_map[absPosition(pos)]->forceChange();
    }
}

Position Map::nearAvaliblePosition(const Position& pos) const
{
    if (isCellEmpty(pos))
    {
        return pos;
    }

    Position curPos = 0;
    int32_t len = 1;
    int32_t count = 0;

    Direction dir = Math::randDirection();
    Position addPos = Math::positionOffset(dir);

    curPos += addPos;
    ++count;

    // if the current dir is NE, SE, SW, NW then rotating
    // the dir at clockwise to next main angle  (N, S, W, E)
    if (static_cast<int>(dir) % 2)
    {
        dir = Math::normalizeDirection(static_cast<int>(dir) + 1);
    }

    // to rotate at clockwise to next angle 90 and get new offset
    dir = Math::normalizeDirection(static_cast<int>(dir) + 2);
    addPos = Math::positionOffset(dir);

    while(!isCellEmpty(pos + curPos))
    {
        if (count >= 8 * len)
        {
            ++len;
            // to rotate at counter-clockwise
            Direction cc_dir = Math::normalizeDirection(static_cast<int>(dir) - 2);
            curPos += Math::positionOffset(cc_dir);
            count = 0;
        }

        if (std::abs(curPos.x() + addPos.x()) > len || std::abs(curPos.y() + addPos.y()) > len)
        {
            dir = Math::normalizeDirection(static_cast<int>(dir) + 2);
            addPos = Math::positionOffset(dir);
        }

        ++count;
        curPos += addPos;
    }

    return pos + curPos;
}

VectorAnts Map::nearestEnemies(const Position& pos, int16_t radius) const
{
    return {};
}

Position Map::nearestFood(const Position& pos, uint32_t visible) const
{
    std::vector<const Position*> arrMinDist;
    //auto visibleCells = Math::visibleCells(pos, visible);
    //uint32_t minDist = 0xFFFFFFFFU;

    //for (auto& posCell : visibleCells) {
    //	auto pCell = cell(posCell).lock();

    //	if (!pCell->food()) {
    //		continue;
    //	}

    //	uint32_t dist = Math::distanceTo(pos, posCell);
    //	if (dist < minDist) {
    //		arrMinDist.clear();
    //		arrMinDist.push_back(&posCell);
    //	} else if (dist == minDist) {
    //		arrMinDist.push_back(&posCell);
    //	}
    //}

    //if (arrMinDist.empty()) {
    //	return Position(-1, -1);
    //}

    uint32_t idx = static_cast<uint32_t>(Math::random(0, arrMinDist.size() - 1));

    return *arrMinDist[idx];
}

void Map::moveAnt(const AntPtr& ant, const Position& pos)
{
    int32_t old_idx = absPosition(ant->position());
    int32_t new_idx = absPosition(pos);

    m_map[new_idx]->setAnt(ant);
    m_map[old_idx]->removeAnt();
    ant->setPosition(pos);
}

void Map::createMap(uint32_t w, uint32_t h)
{
    m_map.clear();

    m_size.init(w, h);
    m_map.resize(m_size.x() * m_size.y());

    Position pos;
    for (auto& cell : m_map)
    {
        cell = std::make_shared<Cell>(pos);
        incPosition(pos);
    }
}

void Map::incPosition(Position& pos, uint32_t x) const
{
    pos.addX(x);

    if (pos.x() >= m_size.x())
    {
        pos.addY(pos.x() - m_size.x() + 1);
        pos.setX(m_size.x() - 1);
    }
}

int32_t Map::absPosition(const Position& pos) const
{
    if (m_conf->isBordered())
    {
        return (pos.x() >= 0 && pos.x() < m_size.x() && pos.y() >= 0 && pos.y() < m_size.y()) ? pos.x() + pos.y() * m_size.x() : 0xffffffff;
    }
    return 0xffffffff; //TODO Issue-2
}

};
