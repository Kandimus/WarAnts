#include "function.h"
#include "Statetment.h"

namespace WarAnts
{
namespace Asm
{

Function::~Function()
{
    DELETE_POINTER(m_stat);

    DELETE_POINTER(m_next);
}

}; // namespace Asm
}; // namespace WarAnts
