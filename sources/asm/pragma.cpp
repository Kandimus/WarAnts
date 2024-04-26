#include "pragma.h"

namespace WarAnts
{
namespace Asm
{

Pragma::~Pragma()
{
    DELETE_POINTER(m_next);
}


}; // namespace Asm
}; // namespace WarAnts
