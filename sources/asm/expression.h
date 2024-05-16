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

class BaseRegister
{
public:
    BaseRegister(uint8_t reg) : m_reg(reg) {}
    virtual bool isPosition() const = 0;
    virtual uint8_t reg() const { return m_reg; }
protected:
    uint8_t m_reg;
};

class CReg : public BaseRegister
{
public:
    CReg(uint8_t reg) : BaseRegister(reg) {}
    bool isPosition() const override { return false; }
};

class PReg : public BaseRegister
{
public:
    PReg(uint8_t reg) : BaseRegister(reg) {}
    bool isPosition() const override { return true; }
};

class Expression : public BaseNode
{
    NOCOPY_STRUCT(Expression)

public:
    Expression(const BaseRegister& reg, BaseNode* parent)
        : BaseNode(parent)
    {
        m_left = nullptr;
        m_right = nullptr;
        m_type = ExpressionType::Register;
        m_value.reg = reg.reg() | (reg.isPosition() ? Register::POSITION : 0);
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
    int8_t reg() const { return m_value.reg; }

    Statement* extrudeExpression(bool isDst, Code* code);
    int8_t compile(int16_t& val, Code* code) const;
    std::string toString() const;

protected:
    bool isPosition() const;
    void deleteSubExpr(Expression** expr);

protected:
    union ExpressionValue
    {
        uint8_t reg;
        int16_t num;
        OperandType op;
    };

    ExpressionType m_type;
    ExpressionValue m_value;

    Expression* m_left = nullptr;
    Expression* m_right = nullptr;
};

inline bool isPositionRegister(int8_t reg)
{
    return reg & Register::POSITION;
}

}; // namespace Asm
}; // namespace WarAnts
