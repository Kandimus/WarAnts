#include "define.h"

namespace WarAnts
{
namespace Asm
{

Define::~Define()
{
    DELETE_POINTER(m_next);
}


}; // namespace Asm
}; // namespace WarAnts
