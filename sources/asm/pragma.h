#pragma once

#include <memory>
#include <string>
#include "baseNode.h"

namespace WarAnts
{
namespace Asm
{

class Pragma : public BaseNode
{
    NOCOPY_STRUCT(Pragma)

public:
    Pragma(PragmaType type, const std::string& value, BaseNode* parent)
        : BaseNode(parent)
    {
        m_type = type;
        m_value = value.substr(1, value.size() - 2);
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
    Pragma* next() const { return m_next; }

    PragmaType type() const { return m_type; }
    const std::string& value() const { return m_value; }

protected:
    PragmaType m_type;
    std::string m_value = "";

    Pragma* m_next = nullptr;
};

}; // namespace Asm
}; // namespace WarAnts
