#include "Statetment.h"

#include "defines.h"

#include "code.h"
#include "expression.h"

namespace WarAnts
{
namespace Asm
{

/*

| 0 ... 5 | 6 ... 10 | 11 ... 15 |
 ----+---- ----+----- -----+-----
     |         |           |
     |         |           +--- source
     |         +--------------- destination
     +------------------------- command code



*/
Statetment* Statetment::extrudeExpression(Code* code)
{
    Statetment* out = nullptr;

    if (m_dst)
    {
        if (m_dst->type() == ExpressionType::Address || m_dst->type() == ExpressionType::Operand)
        {

        }
    }

    if (m_src)
    {
    }
}

bool Statetment::compile(Code* code)
{
    m_offset = code->offset();

    if (type() == StatetmentType::Label)
    {
        return true;
    }

    int16_t command = 0;
    int8_t dst = 0;
    int8_t src = 0;

    switch (m_cmd)
    {
        case AsmCommand::AND:
            //code->addCode();
            command = ((int8_t)AsmCommand::AND) & 0x3f;
            dst = m_dst->compile(true);
            src = m_src->compile(false);
            break;

        default:
            SU_BREAKPOINT();
            return false;
    }

    return true;
}

}; // namespace Asm
}; // namespace WarAnts
