#pragma once

#include <stdint.h>
#include <memory>

#include "log.h"

#include "Position.h"

namespace WarAnts
{

class Ant;

class Cell
{
public:
    Cell(const Position& pos) : m_pos(pos) {}
    Cell(uint32_t x, uint32_t y) : m_pos(x, y) {}
    virtual ~Cell() = default;

    inline bool isChanged() const { return m_isChanged; }
    inline bool isEmpty() const { return !m_status && !m_ant; }
    inline bool isStone () const { return m_status == STONE; }
    inline uint32_t food() const { return isStone() ? 0 : m_status; }
    inline Ant* ant() const { return m_ant; }

    void setFood(uint32_t count)
    {
        if (!m_ant && !isStone())
        {
            m_status += count & 0x7FFFFFFF;
            m_isChanged = true;
        }
        else
        {
            LOGE("Cell[%i, %i]: can not add Food (%i)", m_pos.x(), m_pos.y(), count);
        }
    }
    void setAnt(Ant* ant);
    void removeAnt()
    {
        if (m_ant)
        {
            m_ant = nullptr;
            m_isChanged = true;
        }
    }
    void setStone(bool isstone)
    {
        if (isstone == isStone())
        {
            return;
        }

        if (isstone)
        {
            if (isEmpty())
            {
                m_status = STONE;
                m_isChanged = true;
            }
            else
            {
                LOGE("Cell[%i, %i]: can not set a stone", m_pos.x(), m_pos.y());
            }
        }
        else
        {
            if (isStone())
            {
                m_status = 0;
                m_isChanged = true;
            }
            else
            {
                LOGE("Cell[%i, %i]: can not remove a stone", m_pos.x(), m_pos.y());
            }
        }
    }

    void forceChange()
    {
        m_isChanged = true;
    }

    void clearChanged()
    {
        m_isChanged = false;
    }

protected:
    const uint32_t STONE = 0xFFFFFFFF;
    Position m_pos;
    uint32_t m_status = 0;
    Ant* m_ant = nullptr;
    bool m_isChanged = false;
};

};
