#pragma once

#include <string>
#include "asm_defines.h"

namespace WarAnts
{
namespace Asm
{

struct Statetment;

struct Function
{
    NOCOPY_STRUCT(Function)

    Function(const std::string& name, Statetment* stat)
    {
        m_stat = stat;
        m_name = name;
        m_next = nullptr;
    }
    virtual ~Function();

    Statetment* add(Statetment* next)
    {
        m_next = next;
    }

    std::string m_name = "";
    Statetment* m_stat = nullptr;

    Statetment* m_next = nullptr;
};

}; // namespace Asm
}; // namespace WarAnts
