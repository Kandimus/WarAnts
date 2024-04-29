#pragma once

#include <memory>
#include <string>
#include "baseNode.h"

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

class Pragma : public BaseNode
{
    NOCOPY_STRUCT(Pragma)

public:
    Pragma(PragmaType type, const std::string& value, BaseNode* parent)
        : BaseNode(parent)
    {
        m_type = type;
        m_value = value;
        m_next = nullptr;

        printf("Pragma::Pragma(%i, '%s')\n", (int)type, value.c_str());
    }
    virtual ~Pragma()
    {
        printf("Pragma::~Pragma()\n");
    }

    Pragma* add(Pragma* next)
    {
        m_next = next;
        return this;
    }

    PragmaType m_type;
    std::string m_value = "";

    Pragma* m_next = nullptr;
};

}; // namespace Asm
}; // namespace WarAnts
