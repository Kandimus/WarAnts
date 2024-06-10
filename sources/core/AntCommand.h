#pragma once

#include <stdint.h>

#include "Position.h"

namespace WarAnts
{

namespace Command
{
enum Type
{
                  // Position | Value
    Idle,         //    -     | turn count, if it is 0, then the command will be completed
    MovePos,      //    +     | -
    Attack,       //    +     | 0 - movint to position, 1 - attack enemy
    Feed,
    TakeFood,
    Eat,
    Cater,

    CreateSolder,
    CreateWorker,
};

enum Stage : int16_t
{
    StageMovingToPoint = 0,
    StageMovingToAttack,
    StageAttacking,
};

}

class AntCommand
{
public:
    AntCommand() = default;
    AntCommand(Command::Type cmd)
        : m_type(cmd)
    {}
    AntCommand(Command::Type cmd, const Position& pos)
        : m_type(cmd), m_pos(pos)
    {}
    AntCommand(Command::Type cmd, int16_t x, int16_t y)
        : m_type(cmd), m_pos(x, y)
    {}

    AntCommand(Command::Type cmd, int16_t value)
        : m_type(cmd), m_value(value)
    {}

    void set(Command::Type cmd, int16_t x, int16_t y, int16_t value)
    {
        set(cmd, Position(x, y), value);
    }

    void set(Command::Type cmd, const Position& pos, int16_t value)
    {
        clear();

        m_type = cmd;
        m_pos = pos;
        m_value = value;
    }

    void clear()
    {
        m_type = Command::Idle;
        m_pos = 0;
        m_value = 0;
        m_isCompleted = false;
        //m_abortingCount = 0;
        //m_lengthToPoint = 0xffff;
    }

    void setCompleted(bool val) { m_isCompleted = val; }
    bool isCompleted() const { return m_isCompleted; }

public:
    Command::Type m_type = Command::Idle;
    Position m_pos = 0;
    int16_t m_value = 0;
    AntPtr m_target;
    bool m_isCompleted = false;
    bool m_isFoodCell = false;
};


};
