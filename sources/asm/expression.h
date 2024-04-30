#pragma once

#include <string>
#include "baseNode.h"

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
    RA, // специальный регистр для вычисления адреса
    IF,
    IR,
};

union ExpressionValue
{
    RegisterType reg;
    int16_t num;
    OperandType op;
};

class Expression : public BaseNode
{
    NOCOPY_STRUCT(Expression)

public:
    Expression(RegisterType reg, BaseNode* parent)
        : BaseNode(parent)
    {
        m_left = nullptr;
        m_right = nullptr;
        m_type = ExpressionType::Register;
        m_value.reg = reg;
    }
    Expression(int16_t num, BaseNode* parent)
        : BaseNode(parent)
    {
        m_left = nullptr;
        m_right = nullptr;
        m_type = ExpressionType::Number;
        m_value.num = num;
    }
    Expression(OperandType op, Expression* left, Expression* right, BaseNode* parent)
        : BaseNode(parent)
    {
        m_left = left;
        m_right = right;
        m_type = ExpressionType::Operand;
        m_value.op = op;
    }
    Expression(Expression* left, BaseNode* parent)
        : BaseNode(parent)
    {
        m_left = left;
        m_right = nullptr;
        m_type = ExpressionType::Address;
        m_value.num = 0;
    }
    virtual ~Expression() = default;

    ExpressionType m_type;
    ExpressionValue m_value;

    Expression* m_left = nullptr;
    Expression* m_right = nullptr;
};

}; // namespace Asm
}; // namespace WarAnts
