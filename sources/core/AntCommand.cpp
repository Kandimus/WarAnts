
#include "AntCommand.h"
#include "Ant.h"

namespace WarAnts
{

void AntCommand::clear()
{
    m_type = Command::Type::Idle;
    m_pos = 0;
    m_value = 0;
    m_isCompleted = false;
    m_ant = nullptr;
    m_target = Target::None;
}

void AntCommand::set(Command::Type cmd, Target::Type target, const Position& pos, int16_t value, Ant* ant)
{
    clear();

    m_type = cmd;
    m_target = target;
    m_pos = pos;
    m_value = value;
    m_ant = ant;

    m_pointGoto = pos;
}

Position AntCommand::targetPosition() const
{
    return m_ant ? m_ant->position() : m_pointGoto;
}

} // namespace WarAnts
