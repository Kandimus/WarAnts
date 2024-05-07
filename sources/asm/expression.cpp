#include "expression.h"

#include "defines.h"

#include "code.h"
#include "statement.h"

namespace WarAnts
{
namespace Asm
{

Statement* Expression::extrudeExpression(bool isDst, Code* code)
{
    if (m_type == ExpressionType::Number)
    {
        if (isDst)
        {
            code->error(lineno(), "Numbers can not be using as destination.");
        }

        return nullptr;
    }

    if (m_type == ExpressionType::Register)
    {
        if (isDst && m_value.reg == RegisterType::RF)
        {
            code->error(lineno(), "Register `RF` can not be using as destination.");
        }

        return nullptr;
    }

    RegisterType reg = isDst ? RegisterType::RD : RegisterType::RS;

    if (m_type == ExpressionType::Address)
    {
        Statement* statLeft = m_left->extrudeExpression(isDst, code);

        if (!statLeft)
        {
            return nullptr;
        }

        m_left = new Expression(reg, parent());

        return statLeft;
    }

    if (m_type == ExpressionType::Operand)
    {
        Statement* newStat = nullptr;
        Statement* statInit = nullptr;
        Statement* statOper = nullptr;
        Statement* statLeft = m_left ? m_left->extrudeExpression(isDst, code) : nullptr;
        Statement* statRight = m_right ? m_right->extrudeExpression(isDst, code) : nullptr;
        
        if (!statLeft && !statRight)
        {
            statInit = new Statement(AsmCommand::MOV, new Expression(reg, parent()), m_left, parent());
        }
        else
        {
            if (statLeft)
            {
                statInit = statLeft;
                statInit->add(statRight);
            }
            else
            {
                statInit = statRight;
            }
        }

        switch (m_value.op)
        {
            case OperandType::Plus:
                statOper = new Statement(AsmCommand::ADD, new Expression(reg, parent()), m_right, parent());
                break;

            case OperandType::Minus:
                statOper = new Statement(AsmCommand::SUB, new Expression(reg, parent()), m_right, parent());
                break;

            case OperandType::Star:
                statOper = new Statement(AsmCommand::MUL, new Expression(reg, parent()), m_right, parent());
                break;

            default:
                code->error(lineno(), "Undefined operator.");
                SU_BREAKPOINT();
                return nullptr;
        }

        if (statInit)
        {
            statInit->add(statOper);
        }
        else
        {
            statInit = statOper;
        }

        if (m_left)
        {
            m_left->removeFromParent();
            delete m_left;
            m_left = nullptr;
        }

        if (m_right)
        {
            m_right->removeFromParent();
            delete m_right;
            m_right = nullptr;
        }

        m_type == ExpressionType::Register;
        m_value.reg = reg;

        return statInit;
    }

    return nullptr;
}

int8_t Expression::compile(bool isDst, int16_t& val, Code* code) const
{
    if (m_type == ExpressionType::Number)
    {
        val = m_value.num;
        return int8_t(m_value.num >= -128 && m_value.num <= 127 ? RegisterType::CHAR : RegisterType::SHORT);
    }

    if (m_type == ExpressionType::Register)
    {
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

std::string Expression::toString() const
{
    if (m_type == ExpressionType::Number)
    {
        return std::to_string(m_value.num);
    }

    if (m_type == ExpressionType::Register)
    {
        switch (m_value.reg)
        {
            case RegisterType::R0: return "R0";
            case RegisterType::R1: return "R1";
            case RegisterType::R2: return "R2";
            case RegisterType::RC: return "RC";
            case RegisterType::P0X: return "P0:X";
            case RegisterType::P0Y: return "P0:Y";
            case RegisterType::P1X: return "P1:X";
            case RegisterType::P1Y: return "P1:Y";
            case RegisterType::P2X: return "P2:X";
            case RegisterType::P2Y: return "P2:Y";
            case RegisterType::RF: return "RF";
            case RegisterType::RD: return "RD";
            case RegisterType::RS: return "RS";
            case RegisterType::P0: return "P0";
            case RegisterType::P1: return "P1";
            case RegisterType::P2: return "P2";
            default: return "UNDEFINE REG " + std::to_string((uint32_t)m_value.reg);
        }
    }

    if (m_type == ExpressionType::Address)
    {
        return "[" + m_left->toString() + "]";
    }

    switch (m_value.op)
    {
        case OperandType::Plus:  return "(" + m_left->toString() + " + " + m_right->toString() + ")";
        case OperandType::Minus: return "(" + m_left->toString() + " - " + m_right->toString() + ")";
        case OperandType::Star:  return "(" + m_left->toString() + " * " + m_right->toString() + ")";
        default: return "<Undefined operator>";
    }
    return "<Undefined expression>";
}

}; // namespace Asm
}; // namespace WarAnts
