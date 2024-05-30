#include "cell.h"

#include "ant.h"

namespace WarAnts
{

void Cell::setAnt(Ant* ant)
{
    if (isEmpty())
    {
        m_ant = ant;
        m_isChanged = true;
    }
    else
    {
        LOGE("Cell[%i, %i]: can not move %s", m_pos.x(), m_pos.y(), ant->toString().c_str());
    }
}

};