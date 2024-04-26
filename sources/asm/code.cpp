#include "code.h"
#include "function.h"
#include "pragma.h"

namespace WarAnts
{
namespace Asm
{

Code::~Code()
{
    DELETE_POINTER(m_pragma);
    DELETE_POINTER(m_function);
}

}; // namespace Asm
}; // namespace WarAnts
