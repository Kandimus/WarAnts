#pragma once

#include <string>
#include "baseNode.h"

namespace WarAnts
{
namespace Asm
{

class Code;
class Expression;

enum class StatetmentType
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

class Statetment : public BaseNode
{
    NOCOPY_STRUCT(Statetment)

public:
    // label
    Statetment(const std::string& label, BaseNode* parent)
        : BaseNode(parent)
    {
        m_dst = nullptr;
        m_src = nullptr;
        m_cmd = AsmCommand::NOP;
        m_type = StatetmentType::Label;
        m_label = label;
        m_next = nullptr;
    }
    // normal
    Statetment(AsmCommand cmd, Expression* dst, Expression* src, BaseNode* parent)
        : BaseNode(parent)
    {
        m_dst = dst;
        m_src = src;
        m_type = StatetmentType::Command;
        m_cmd = cmd;
        m_next = nullptr;
    }
    // single
    Statetment(AsmCommand cmd, Expression* dst, BaseNode* parent)
        : BaseNode(parent)
    {
        m_dst = dst;
        m_src = nullptr;
        m_type = StatetmentType::Command;
        m_cmd = cmd;
        m_next = nullptr;
    }
    // without params
    Statetment(AsmCommand cmd, BaseNode* parent)
        : BaseNode(parent)
    {
        m_dst = nullptr;
        m_src = nullptr;
        m_type = StatetmentType::Command;
        m_cmd = cmd;
        m_next = nullptr;
    }
    // call, jumps
    Statetment(AsmCommand cmd, const std::string& label, BaseNode* parent)
        : BaseNode(parent)
    {
        m_dst = nullptr;
        m_src = nullptr;
        m_cmd = cmd;
        m_type = StatetmentType::Command;
        m_jump = label;
        m_next = nullptr;
    }
    virtual ~Statetment() = default;

    Statetment* add(Statetment* next)
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

    StatetmentType type() const
    {
        return m_type;
    }

    Statetment* next() const
    {
        return m_next;
    }

    Statetment* extrudeExpression(Code* code);
    bool compile(Code* code);

public:
    StatetmentType m_type;
    AsmCommand  m_cmd;
    Expression* m_dst = nullptr;
    Expression* m_src = nullptr;
    std::string m_label = "";
    std::string m_jump = "";

    Statetment* m_next = nullptr;
};

}; // namespace Asm
}; // namespace WarAnts
