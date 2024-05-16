#pragma once

#include <string>
#include <vector>
#include "baseNode.h"

namespace WarAnts
{
namespace Asm
{

class Code;
class Statement;

class Expression : public BaseNode
{
    NOCOPY_STRUCT(Expression)

public:
    Expression(Register::Type reg, BaseNode* parent)
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
    Expression(Expression* left, bool posAdr, BaseNode* parent)
        : BaseNode(parent)
    {
        m_left = left;
        m_right = nullptr;
        m_type = ExpressionType::Address;
        m_value.num = posAdr;
    }
    virtual ~Expression() = default;

    ExpressionType type() const { return m_type; }
    Register::Type reg() const { return m_value.reg; }

    Statement* extrudeExpression(bool isDst, Code* code);
    int8_t compile(bool isDst, int16_t& val, Code* code) const;
    std::string toString() const;

protected:
    bool isPosition() const;
    void deleteSubExpr(Expression** expr);

protected:
    union ExpressionValue
    {
        Register::Type reg;
        int16_t num;
        OperandType op;
    };

    ExpressionType m_type;
    ExpressionValue m_value;

    Expression* m_left = nullptr;
    Expression* m_right = nullptr;
};

inline bool isPositionRegister(const Register::Type& reg)
{
    return reg == Register::P0 || reg == Register::P1 || reg == Register::P2;
}

}; // namespace Asm
}; // namespace WarAnts
