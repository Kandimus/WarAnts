#pragma once

#include <string>
#include "BaseNode.h"

namespace WarAnts
{
namespace Asm
{

class Statetment;

class Function : public BaseNode
{
    NOCOPY_STRUCT(Function)

public:
    Function(const std::string& name, Statetment* stat, BaseNode* parent)
        : BaseNode(parent)
    {
        m_stat = stat;
        m_name = name;
        m_next = nullptr;
        printf("Function(%s)\n", name.c_str());
    }
    virtual ~Function() = default;

    Function* add(Function* next)
    {
        m_next = next;
        return this;
    }

public:
    std::string m_name = "";
    Statetment* m_stat = nullptr;

    Function* m_next = nullptr;
};

}; // namespace Asm
}; // namespace WarAnts
