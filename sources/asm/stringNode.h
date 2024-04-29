#pragma once

#include <string>
#include "baseNode.h"

namespace WarAnts
{
namespace Asm
{

class StringNode : BaseNode
{
public:
    StringNode(const char* text, BaseNode* parent)
        : BaseNode(parent)
    {
        m_text = text;
    }
    virtual ~StringNode() = default;

    const std::string& get() const
    {
        return m_text;
    }

protected:
    std::string m_text;
};

}; // namespace Asm
}; // namespace WarAnts
