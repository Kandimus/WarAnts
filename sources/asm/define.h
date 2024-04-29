#pragma once

#include <string>
#include "asm_defines.h"

namespace WarAnts
{
namespace Asm
{

struct Define
{
    NOCOPY_STRUCT(Define)

    Define(const std::string& name, int16_t val)
    {
        m_value = val;
        m_name = name;
        m_next = nullptr;
    }
    virtual ~Define();

    Define* add(Define* next)
    {
        m_next = next;
        return this;
    }

    std::string m_name = "";
    int16_t m_value = 0;

    Define* m_next = nullptr;
};

}; // namespace Asm
}; // namespace WarAnts
