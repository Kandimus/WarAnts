#include "statetment.h"
#include "expression.h"

namespace WarAnts
{
namespace Asm
{

Statetment::~Statetment()
{
    DELETE_POINTER(m_dst);
    DELETE_POINTER(m_src);
    DELETE_POINTER(m_next);
}

}; // namespace Asm
}; // namespace WarAnts
