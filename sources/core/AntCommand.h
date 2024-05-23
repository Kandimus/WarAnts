#pragma once

#include <stdint.h>

#include "Position.h"

namespace WarAnts
{

enum class CommandType
{
    Idle,
    MovePos,
    Attack, 
    Eat,
    TakeFood,
    Feed,

    CreateSolder,
    CreateWorker,
};

class AntCommand
{
public:
    AntCommand() = default;
    AntCommand(CommandType cmd)
        : m_type(cmd)
    {}
    AntCommand(CommandType cmd, const Position& pos)
        : m_type(cmd), m_pos(pos)
    {}
    AntCommand(CommandType cmd, int16_t x, int16_t y)
        : m_type(cmd), m_pos(x, y)
    {}

    AntCommand(CommandType cmd, int16_t value)
        : m_type(cmd), m_value(value)
    {}

    void set(CommandType cmd, int16_t x, int16_t y, int16_t value)
    {
        m_type = cmd;
        m_pos = Position(x, y);
        m_value = value;
    }

    void clear()
    {
        m_type = CommandType::Idle;
        m_pos = 0;
        m_value = 0;
    }

public:
    CommandType m_type = CommandType::Idle;
    Position m_pos = 0;
    int16_t m_value = 0;
};


};
