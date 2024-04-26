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
    ADD,
    AND,

    BSF,
    BSR,

    MOV,

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
    virtual ~Statetment();

    Statetment* add(Statetment* next)
    {
        m_next = next;
    }

    StatetmentType m_type;
    AsmCommand  m_cmd;
    Expression* m_dst = nullptr;
    Expression* m_src = nullptr;
    std::string m_label = "";

    Statetment* m_next = nullptr;
};

}; // namespace Asm
}; // namespace WarAnts
