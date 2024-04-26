#include "expression.h"

namespace WarAnts
{
namespace Asm
{

Expression::~Expression()
{
    DELETE_POINTER(m_left);
    DELETE_POINTER(m_right);
}

}; // namespace Asm
}; // namespace WarAnts
