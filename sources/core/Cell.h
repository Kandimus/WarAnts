#pragma once

#include <stdint.h>
#include <memory>

#include "log.h"

#include "Position.h"

namespace WarAnts
{

namespace
{
    const int16_t STONE = -32768; // 0x8000
}

class Ant;

class Cell
{
public:
    Cell(const Position& pos) : m_pos(pos) {}
    Cell(uint32_t x, uint32_t y) : m_pos(x, y) {}
    virtual ~Cell() = default;

    inline bool isChanged() const { return m_isChanged; }
    inline bool isEmpty() const { return !m_status && !m_ant; }
    inline bool isStone () const { return m_status & STONE; }
    inline int16_t food() const { return isStone() ? 0 : m_status; }
    inline Ant* ant() const { return m_ant; }
    inline Position position() const { return m_pos; }

    void modifyFood(int16_t count)
    {
        if (!m_ant && !isStone())
        {
            m_status += count;
            m_status = m_status < 0 ? 0 : m_status;
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
    Position m_pos;
    int16_t m_status = 0;
    Ant* m_ant = nullptr;
    bool m_isChanged = false;
};

};
