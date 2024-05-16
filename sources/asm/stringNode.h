#pragma once

#include "stringex.h"
#include "baseNode.h"

namespace WarAnts
{
namespace Asm
{

class StringNode : public BaseNode
{
public:
    StringNode(const char* text, BaseNode* parent)
        : BaseNode(parent)
    {
        m_text = su::String_tolower(text);
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
