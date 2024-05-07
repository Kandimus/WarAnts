#include "expression.h"

#include "defines.h"

#include "code.h"

namespace WarAnts
{
namespace Asm
{

int8_t Expression::compile(bool isDst, int16_t& val, Code* code) const
{
    if (m_type == ExpressionType::Number)
    {
        val = m_value.num;
        return int8_t(m_value.num >= -128 && m_value.num <= 127 ? RegisterType::CHAR : RegisterType::SHORT);
    }

    if (m_type == ExpressionType::Register)
    {
        if (isDst && m_value.reg == RegisterType::RF)
        {
            code->error(lineno(), "Register RF can not using as destination.");
            return -1;
        }

        return (int8_t)m_value.reg;
    }

    if (m_type == ExpressionType::Address)
    {
        int16_t val = 0;
        auto reg = m_left->compile(isDst, val, code);

        return reg | 0x80;
    }

    SU_BREAKPOINT();
    return -1;
}

}; // namespace Asm
}; // namespace WarAnts
