#pragma once

#include <fstream>
#include <string>

#include "baseNode.h"

namespace WarAnts
{
namespace Asm
{

class Code;
class Expression;

enum class StatementType
{
    Label,
    Command,
};


class Statement : public BaseNode
{
    NOCOPY_STRUCT(Statement)

public:
    // label
    Statement(const std::string& label, BaseNode* parent)
        : BaseNode(parent)
    {
        m_dst = nullptr;
        m_src = nullptr;
        m_cmd = AsmCommand::NOP;
        m_type = StatementType::Label;
        m_label = label;
        m_next = nullptr;
    }
    // normal
    Statement(AsmCommand cmd, Expression* dst, Expression* src, BaseNode* parent)
        : BaseNode(parent)
    {
        m_dst = dst;
        m_src = src;
        m_type = StatementType::Command;
        m_cmd = cmd;
        m_next = nullptr;
    }
    // without params
    Statement(AsmCommand cmd, BaseNode* parent)
        : BaseNode(parent)
    {
        m_dst = nullptr;
        m_src = nullptr;
        m_type = StatementType::Command;
        m_cmd = cmd;
        m_next = nullptr;
    }
    // call, jumps
    Statement(AsmCommand cmd, const std::string& label, BaseNode* parent)
        : BaseNode(parent)
    {
        m_dst = nullptr;
        m_src = nullptr;
        m_cmd = cmd;
        m_type = StatementType::Command;
        m_jump = label;
        m_next = nullptr;
    }
    virtual ~Statement() = default;

    Statement* add(Statement* next)
    {
        if (m_next)
        {
            m_next->add(next);
        }
        else
        {
            m_next = next;
        }
        return this;
    }

    StatementType type() const { return m_type; }
    Statement* next() const { return m_next;}

    Statement* extrudeExpression(Code* code);
    bool compile(Code* code);
    void print(std::ofstream& file) const;

protected:
    RegisterType compileExpr(Expression* expr, bool isDst, Code* code);
    void compileDstSrc(BCodeCommand cmd, RegisterType& dst, RegisterType& src, Code* code);
    void compileDst(BCodeCommand cmd, RegisterType& dst, Code* code);
    void compileSrc(BCodeCommand cmd, RegisterType& src, Code* code);
    void compileCommon(BCodeCommand cmd, Code* code);
    void compileCommonDst(BCodeCommand cmd, Code* code);
    void compileCommonSrc(BCodeCommand cmd, Code* code);
    void compileNoPosition(BCodeCommand cmd, Code* code);

public:
    StatementType m_type;
    AsmCommand  m_cmd;
    Expression* m_dst = nullptr;
    Expression* m_src = nullptr;
    std::string m_label = "";
    std::string m_jump = "";

    std::vector<int8_t> m_bcode;

    Statement* m_next = nullptr;
};

}; // namespace Asm
}; // namespace WarAnts
