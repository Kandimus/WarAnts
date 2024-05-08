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
    if (m_type == ExpressionType::Number || m_type == ExpressionType::Register)
    {
        return nullptr;
    }

    RegisterType reg = isDst ? RegisterType::RD : RegisterType::RS;

    if (m_type == ExpressionType::Address)
    {
        Statement* statLeft = m_left->extrudeExpression(isDst, code);

        if (code->hasError())
        {
            return nullptr;
        }

        if (!statLeft)
        {
            return nullptr;
        }

        m_left = new Expression(reg, parent());

        return statLeft;
    }

    if (m_type != ExpressionType::Operand)
    {
        SU_BREAKPOINT();
        return nullptr;
    }

    Statement* statLeft = m_left->extrudeExpression(isDst, code);
    Statement* statRight = m_right->extrudeExpression(isDst, code);

    if (code->hasError())
    {
        return nullptr;
    }

    if (m_left->isPosition())
    {
        code->error(lineno(), "Position registers can not be using in expressions.");
        return nullptr;
    }

    if (m_right->isPosition())
    {
        code->error(lineno(), "Position registers can not be using in expressions.");
        return nullptr;
    }

    Statement* statInit = nullptr;
    Expression* expr = m_right;

    if (!statLeft && !statRight)
    {
        statInit = new Statement(AsmCommand::MOV, new Expression(reg, parent()), m_left, parent());
        m_left = nullptr;
        m_right = nullptr;
    }
    else
    {
        if (statLeft)
        {
            m_right = nullptr;
            statInit = statLeft;
            statInit->add(statRight);
        }
        else
        {
            expr = m_left;
            m_left = nullptr;
            statInit = statRight;
        }
    }

    Statement* statOper = nullptr;
    switch (m_value.op)
    {
        case OperandType::Plus:
            statOper = new Statement(AsmCommand::ADD, new Expression(reg, parent()), expr, parent());
            break;

        case OperandType::Minus:
            statOper = new Statement(AsmCommand::SUB, new Expression(reg, parent()), expr, parent());
            break;

        case OperandType::Star:
            statOper = new Statement(AsmCommand::MUL, new Expression(reg, parent()), expr, parent());
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

    deleteSubExpr(&m_left);
    deleteSubExpr(&m_right);

    m_type = ExpressionType::Register;
    m_value.reg = reg;

    return statInit;
}

int8_t Expression::compile(bool isDst, int16_t& val, Code* code) const
{
    if (m_type == ExpressionType::Number)
    {
        val = m_value.num;
        return (int8_t)(m_value.num >= -128 && m_value.num <= 127 ? RegisterType::CHAR : RegisterType::SHORT);
    }

    if (m_type == ExpressionType::Register)
    {
        return (int8_t)m_value.reg;
    }

    if (m_type == ExpressionType::Address)
    {
        return m_left->compile(isDst, val, code) | 0x80;
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

bool Expression::isPosition() const
{
    if (type() != ExpressionType::Register)
    {
        return false;
    }

    return isPositionRegister(reg());
}

void Expression::deleteSubExpr(Expression** expr)
{
    if (!expr)
    {
        return;
    }

    if (*expr)
    {
        (*expr)->removeFromParent();
        delete *expr;
        *expr = nullptr;
    }
}

}; // namespace Asm
}; // namespace WarAnts
