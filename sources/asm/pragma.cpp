#include "pragma.h"

namespace WarAnts
{
namespace Asm
{

Pragma::~Pragma()
{
    printf("Pragma::~Pragma()\n");
    DELETE_POINTER(m_next);
}


}; // namespace Asm
}; // namespace WarAnts
