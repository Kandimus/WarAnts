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

    uint8_t reg = isDst ? Register::RD : Register::RS;

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

        m_left = new Expression(CReg(reg), parent());

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

    Statement* statInit = nullptr;
    Expression* expr = m_right;

    if (!statLeft && !statRight)
    {
        yyRealLineNo = lineno();
        statInit = new Statement(AsmCommand::MOV, new Expression(CReg(reg), parent()), m_left, parent());
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
            statOper = new Statement(AsmCommand::ADD, new Expression(CReg(reg), parent()), expr, parent());
            break;

        case OperandType::Minus:
            statOper = new Statement(AsmCommand::SUB, new Expression(CReg(reg), parent()), expr, parent());
            break;

        case OperandType::Star:
            statOper = new Statement(AsmCommand::MUL, new Expression(CReg(reg), parent()), expr, parent());
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

int8_t Expression::compile(int16_t& val, Code* code) const
{
    if (m_type == ExpressionType::Number)
    {
        val = m_value.num;
        return m_value.num >= -128 && m_value.num <= 127 ? Register::CHAR : Register::SHORT;
    }

    if (m_type == ExpressionType::Register)
    {
        return (int8_t)m_value.reg;
    }

    if (m_type == ExpressionType::Address)
    {
        return m_left->compile(val, code) | Register::ADDRESS | (m_value.num ? Register::POSITION : 0);
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
        switch (m_value.reg & Register::COUNT)
        {
            case Register::R0: return "R0";
            case Register::R1: return "R1";
            case Register::R2: return "R2";
            case Register::RC: return "RC";
            case Register::P0X: return isPosition() ? "P0" : "P0:X";
            case Register::P0Y: return "P0:Y";
            case Register::P1X: return isPosition() ? "P2" : "P1:X";
            case Register::P1Y: return "P1:Y";
            case Register::P2X: return isPosition() ? "P2" : "P2:X";
            case Register::P2Y: return "P2:Y";
            case Register::RF: return "RF";
            case Register::RD: return "RD";
            case Register::RS: return "RS";
            default: return "UNDEFINE REG " + std::to_string((uint32_t)m_value.reg);
        }
    }

    if (m_type == ExpressionType::Address)
    {
        static std::string bra�ket[2][2] = { {"[", "]"}, {"<", ">"} };
        return bra�ket[m_value.num][0] + m_left->toString() + bra�ket[m_value.num][1];
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
