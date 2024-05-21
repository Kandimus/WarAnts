#pragma once

#include <fstream>
#include <string>
#include "StringNode.h"

namespace WarAnts
{
namespace Asm
{

class Code;
class Statement;
class StringNode;

class Function : public BaseNode
{
    NOCOPY_STRUCT(Function)

public:
    Function(const StringNode* name, Statement* stat, BaseNode* parent)
        : BaseNode(parent)
    {
        m_stat = stat;
        m_name = name->get();
        m_next = nullptr;
        m_lineno = name->lineno();
    }
    virtual ~Function() = default;

    Function* add(Function* next)
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

    Function* next() const { return m_next; }
    const std::string& name() const { return m_name; }

    bool used() const { return m_used; }
    void setUsed(bool used) { m_used = used; }

    bool checkLabelNames(Code* code);
    bool extrudeExpression(Code* code);
    bool compile(Code* code);
    bool optimizeValueStatement(Code* code);
    bool checkReturnStatement(Code* code);
    bool assignOffsets(Code* code);
    bool resolveLabels(bool& recalc, Code* code);
    bool save(Code* code);
    void print(std::ofstream& file);

public:
    std::string m_name = "";
    Statement* m_stat = nullptr;
    bool m_used = false;

    Function* m_next = nullptr;
};

}; // namespace Asm
}; // namespace WarAnts
