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
        m_label = label;
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
    const std::string& label() const { return m_label; }
    Statement* next() const { return m_next;}

    bool isJump() const;
    bool isCall() const;
    int16_t jumpValue() const;
    bool checkUnusedJump() const;

    bool isExit() const;

    bool isValueCommand() const;

    BaseNode* labelPtr() const { return m_labelPtr; }
    void setLabelPtr(BaseNode* label) { m_labelPtr = label; }

    Statement* extrudeExpression(Code* code);
    bool compile(Code* code);
    bool optimizeValueStatement(Code* code);
    bool assignOffsets(Code* code);
    bool resolveLabels(bool& recalc, Code* code);
    bool save(Code* code);
    void print(std::ofstream& file) const;

protected:
    Register::Type compileExpr(Expression* expr, bool isDst, Code* code);
    void compileDstSrc(BCode::Command cmd, Register::Type& dst, Register::Type& src, Code* code);
    void compileDst(BCode::Command cmd, Register::Type& dst, Code* code);
    void compileSrc(BCode::Command cmd, Register::Type& src, Code* code);

    void compileNoArgs(BCode::Command cmd, Code* code);
    void compileCommon(BCode::Command cmd, Code* code);
    void compileDstCommon(BCode::Command cmd, Code* code);
    void compileSrcCommon(BCode::Command cmd, Code* code);
    void compileNoPosition(BCode::Command cmd, Code* code);
    void compileDstNoPosition(BCode::Command cmd, Code* code);
    void compileSrcNoPosition(BCode::Command cmd, Code* code);
    void compileStrong(BCode::Command cmd, Code* code);
    void compileJump(BCode::Command cmdl, Code* code);
    void compilePosition(BCode::Command cmd, Code* code);
    void compileDstPosition(BCode::Command cmd, Code* code);
    void compileDstNoPositionSrcPosition(BCode::Command cmd, Code* code);

public:
    StatementType m_type;
    AsmCommand  m_cmd;
    Expression* m_dst = nullptr;
    Expression* m_src = nullptr;
    std::string m_label = "";
    BaseNode* m_labelPtr = nullptr;

    std::vector<int8_t> m_bcode;

    Statement* m_next = nullptr;
};

}; // namespace Asm
}; // namespace WarAnts
