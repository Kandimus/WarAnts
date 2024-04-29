#pragma once

#include <stdio.h>

#include "asm_defines.h"

namespace WarAnts
{
namespace Asm
{

struct Define;
struct Function;
struct Pragma;

struct Code
{
    NOCOPY_STRUCT(Code)

    Code(Pragma* pragma, Define* define, Function* function)
    {
        m_pragma = pragma;
        m_define = define;
        m_function = function;
        printf("Code:Code\n");
    }
    virtual ~Code();

    Pragma* m_pragma = nullptr;
    Define* m_define = nullptr;
    Function* m_function = nullptr;
};

}; // namespace Asm
}; // namespace WarAnts
