#include "function.h"
#include "code.h"
#include "Statetment.h"

namespace WarAnts
{
namespace Asm
{

bool Function::extrudeExpression(Code* code)
{
    Statetment* stat = m_stat;
    Statetment* prev = nullptr;

    while (stat)
    {
        if (!stat->extrudeExpression(code))
        {
            return false;
        }

        stat = stat->next();
    }

    return true;
}

bool Function::compile(Code* code)
{
    Statetment* stat = m_stat;

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

}; // namespace Asm
}; // namespace WarAnts
