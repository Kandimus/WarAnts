#include "function.h"
#include "code.h"
#include "Statement.h"

namespace WarAnts
{
namespace Asm
{

bool Function::extrudeExpression(Code* code)
{
    Statement* stat = m_stat;
    Statement* prev = nullptr;

    while (stat)
    {
        auto newStat = stat->extrudeExpression(code);

        if (code->hasError())
        {
            return false;
        }

        if (newStat)
        {
            if (prev)
            {
                prev->m_next = newStat;
                newStat->add(stat);
            }
            else
            {
                m_stat = newStat;
                m_stat->add(stat);
            }
        }

        prev = stat;
        stat = stat->next();
    }

    return true;
}

bool Function::compile(Code* code)
{
    Statement* stat = m_stat;

    m_offset = code->offset();

    while (stat)
    {
        if (!stat->compile(code))
        {
            return false;
        }

        stat = stat->next();
    }

    return true;
}

void Function::print(std::ofstream& file)
{
    file << "." << m_name << std::endl;

    Statement* stat = m_stat;

    while (stat)
    {
        stat->print(file);
        stat = stat->next();
    }

    file << std::endl;
}

}; // namespace Asm
}; // namespace WarAnts
