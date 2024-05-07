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

enum class AsmCommand
{
    UNDEF = 0,

    ADD,
    AND,
    DEC,
    DIV,
    INC,
    MOD,
    MUL,
    NEG,
    NOT,
    OR,
    SUB,
    XOR,
    MIN,
    MAX,

    BSF,
    BSR,
    BT,
    BTR,
    BTS,
    BTC,
    SHL,
    SHR,
    ROL,
    ROR,

    EQ,
    NEQ,
    GT,
    GE,
    LT,
    LE,
    TEST,

    JMP,
    JZ,
    JNZ,
    JO,
    JNO,
    JCZ,
    JCNZ,
    LOOP,

    MOV,
    CALL,
    LEN,
    EXIT,

    LDTR,
    LDFD,
    LDEN,
    LDFR,

    CIDL,
    CMOV,
    CATT,
    CTKF,
    CGVF,
    CEAT,
    CPS,
    CPW,

    NOP
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
    // single
    Statement(AsmCommand cmd, Expression* dst, BaseNode* parent)
        : BaseNode(parent)
    {
        m_dst = dst;
        m_src = nullptr;
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

public:
    StatementType m_type;
    AsmCommand  m_cmd;
    Expression* m_dst = nullptr;
    Expression* m_src = nullptr;
    std::string m_label = "";
    std::string m_jump = "";

    Statement* m_next = nullptr;
};

}; // namespace Asm
}; // namespace WarAnts
