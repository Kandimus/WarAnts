#pragma once

#include "asm_defines.h"

namespace WarAnts
{
namespace Asm
{

struct Pragma;
struct Function;

struct Code
{
    NOCOPY_STRUCT(Code)

    Code(Pragma* pragma, Function* function)
    {
        m_pragma = pragma;
        m_function = function;
    }
    virtual ~Code();

    Pragma* m_pragma = nullptr;
    Function* m_function = nullptr;
};

}; // namespace Asm
}; // namespace WarAnts
