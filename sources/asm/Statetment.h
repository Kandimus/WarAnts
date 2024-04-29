#pragma once

#include <string>
#include "asm_defines.h"

namespace WarAnts
{
namespace Asm
{

struct Expression;

enum class StatetmentType
{
    Label,
    Command,
    Full,
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

struct Statetment
{
    NOCOPY_STRUCT(Statetment)

    Statetment(const std::string& label)
    {
        m_dst = nullptr;
        m_src = nullptr;
        m_cmd = AsmCommand::NOP;
        m_type = StatetmentType::Label;
        m_label = label;
        m_next = nullptr;
    }
    Statetment(AsmCommand cmd, Expression* dst, Expression* src)
    {
        m_dst = dst;
        m_src = src;
        m_type = StatetmentType::Command;
        m_cmd = cmd;
        m_next = nullptr;
    }
    Statetment(AsmCommand cmd, const std::string& label)
    {
        m_dst = nullptr;
        m_src = nullptr;
        m_cmd = cmd;
        m_type = StatetmentType::Command;
        m_jump = label;
        m_next = nullptr;
    }
    virtual ~Statetment();

    Statetment* add(Statetment* next)
    {
        m_next = next;
        return this;
    }

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
