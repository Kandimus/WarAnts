#pragma once

#include <stdint.h>

#include "Position.h"

namespace WarAnts
{

enum class CommandType
{
    Idle,
    Move,
    MoveAndEat,
    MoveAndAttack,
    MoveAndFeed,
};

class AntCommand
{
public:
    AntCommand() = default;

    void set(CommandType cmd, int16_t x, int16_t y, int16_t userdata)
    {
        m_type = cmd;
        m_pos = Position(x, y);
        m_userData = userdata;
    }

    void clear()
    {
        m_type = CommandType::Idle;
        m_pos = 0;
        m_userData = 0;
    }

public:
    CommandType m_type = CommandType::Idle;
    Position m_pos = 0;
    int16_t m_userData = 0;
};


};
