#pragma once

#include <vector>
#include "asm_defines.h"

namespace WarAnts
{
namespace Asm
{

class BaseNode
{
public:
    BaseNode(BaseNode* parent)
    {
        m_parent = parent;

        if (m_parent)
        {
            m_parent->addChild(this);
        }
    }
    virtual ~BaseNode()
    {
        for (auto node : m_child)
        {
            delete node;
        }
        m_child.clear();
    }

    void addChild(BaseNode* node)
    {
        if (m_child.empty())
        {
            m_child.reserve(1024);
        }

        m_child.push_back(node);
    }

    uint32_t lineno() const
    {
        return m_lineno;
    }

protected:
    uint32_t m_lineno = 0;

private:
    BaseNode* m_parent = nullptr;
    std::vector<BaseNode*> m_child;
};

}; // namespace Asm
}; // namespace WarAnts
