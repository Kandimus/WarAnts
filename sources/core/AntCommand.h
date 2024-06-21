#pragma once

#include <stdint.h>

#include "Position.h"

namespace WarAnts
{

class Ant;

namespace Command
{
enum Type : uint8_t
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
} //namespace Command

namespace Target
{
enum Type : uint8_t
{
    None = 0,
    Ant,
    Food,
};
} //namespace Target

class AntCommand
{
public:
    AntCommand() = default;
    //AntCommand(Command::Type cmd)
    //    : m_type(cmd)
    //{}
    //AntCommand(Command::Type cmd, const Position& pos)
    //    : m_type(cmd), m_pos(pos)
    //{}
    //AntCommand(Command::Type cmd, int16_t x, int16_t y)
    //    : m_type(cmd), m_pos(x, y)
    //{}

    //AntCommand(Command::Type cmd, int16_t value)
    //    : m_type(cmd), m_value(value)
    //{}

    //void set(Command::Type cmd, int16_t x, int16_t y, int16_t value)
    //{
    //    set(cmd, Position(x, y), value);
    //}

    //void set(Command::Type cmd, const Position& pos, int16_t value)
    //{
    //    clear();

    //    m_type = cmd;
    //    m_pos = pos;
    //    m_value = value;
    //}

    //void clear()
    //{
    //    m_type = Command::Idle;
    //    m_pos = 0;
    //    m_value = 0;
    //    m_isCompleted = false;
    //    m_ant = nullptr;
    //    m_target = Target::None;
    //}

    inline bool isCompleted() const { return m_isCompleted; }
    inline void setCompleted(bool val) { m_isCompleted = val; }

    inline Target::Type target() const { return m_target; }
    inline void setTarget(Target::Type val) { m_target = val; }

    inline Ant* ant() { return m_ant; }
    inline const Ant* ant() const { return m_ant; }
    inline void setAnt(Ant* target) { m_ant = target; }

    inline const Position& position() const { return m_pos; }
    inline void setPosition(const Position& pos) { m_pos = pos; }

public:
    Command::Type m_type = Command::Idle;
    int16_t m_value = 0;

protected:
    Position m_pos = 0;
    Ant* m_ant = nullptr;
    bool m_isCompleted = false;
    Target::Type m_target = Target::None;
};


};
