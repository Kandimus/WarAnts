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
    Core,
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
    }
    virtual ~Pragma() = default;

    Pragma* add(Pragma* next)
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

    PragmaType m_type;
    std::string m_value = "";

    Pragma* m_next = nullptr;
};

}; // namespace Asm
}; // namespace WarAnts
