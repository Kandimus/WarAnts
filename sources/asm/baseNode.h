#pragma once

#include <vector>
#include "asm_defines.h"

// Flex/Bison
extern int yylineno;

namespace WarAnts
{
namespace Asm
{

class BaseNode
{
public:
    BaseNode(BaseNode* parent)
    {
        m_lineno = yylineno;
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
            if (node)
            {
                delete node;
            }
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

    void removeChild(BaseNode* node)
    {
        for (size_t ii = 0; ii < m_child.size(); ++ii)
        {
            if (m_child[ii] == node)
            {
                //TODO можно заменить на обнуление
                m_child.erase(m_child.begin() + ii);
                return;
            }
        }
    }

    void removeFromParent()
    {
        if (!m_parent)
        {
            return;
        }

        m_parent->removeChild(this);
        m_parent = nullptr;
    }

    BaseNode* parent() const { return m_parent; }
    int32_t lineno() const { return m_lineno; }
    int16_t offset() const { return m_offset; }

protected:
    int32_t m_lineno = 0;
    int16_t m_offset = 0;

private:
    BaseNode* m_parent = nullptr;
    std::vector<BaseNode*> m_child;
};

}; // namespace Asm
}; // namespace WarAnts
