#pragma once

#include <memory>
#include <string>
#include "asm_defines.h"

namespace WarAnts
{
namespace Asm
{

enum class PragmaType
{
    Class,
    Name,
    Version,
};

struct Pragma
{
    Pragma(PragmaType type, const std::string& value)
    {
        m_type = type;
        m_value = value;
        m_next = nullptr;
        printf("Pragma::Pragma(%i, '%s')\n", (int)type, value.c_str());
    }
    virtual ~Pragma() = default;

    Pragma* add(std::shared_ptr<Pragma>& next)
    {
        m_next = next;
        return this;
    }

    PragmaType m_type;
    std::string m_value = "";

    std::shared_ptr<Pragma> m_next = nullptr;
};

}; // namespace Asm
}; // namespace WarAnts
