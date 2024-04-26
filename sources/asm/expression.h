#pragma once

#include "asm_defines.h"

namespace WarAnts
{
namespace Asm
{

enum class ExpressionType
{
    Register,
    Number,
    Operand,
    Address,
};

enum class OperandType
{
    Plus,
    Minus,
    Star,
};

enum class RegisterType
{
    R0,
    R1,
    R2,
    R3,
    RC,
    RF,
    RA, // ����������� ������� ��� ���������� ������
    IF,
    IR,
};

union ExpressionValue
{
    RegisterType reg;
    int16_t num;
    OperandType op;
};

struct Expression
{
    NOCOPY_STRUCT(Expression)

    Expression(RegisterType reg)
    {
        m_left = nullptr;
        m_right = nullptr;
        m_type = ExpressionType::Register;
        m_value.reg = reg;
    }
    Expression(int16_t num)
    {
        m_left = nullptr;
        m_right = nullptr;
        m_type = ExpressionType::Number;
        m_value.num = num;
    }
    Expression(OperandType op, Expression* left, Expression* right)
    {
        m_left = left;
        m_right = right;
        m_type = ExpressionType::Operand;
        m_value.op = op;
    }
    Expression(OperandType op, Expression* left)
    {
        m_left = left;
        m_right = nullptr;
        m_type = ExpressionType::Address;
        m_value.num = 0;
    }
    virtual ~Expression();

    ExpressionType m_type;
    ExpressionValue m_value;

    Expression* m_left = nullptr;
    Expression* m_right = nullptr;
};

}; // namespace Asm
}; // namespace WarAnts