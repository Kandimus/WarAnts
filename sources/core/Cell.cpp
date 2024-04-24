#include "cell.h"

#include "ant.h"

namespace WarAnts
{

void Cell::setAnt(const std::shared_ptr<Ant>& ant)
{
    if (isEmpty())
    {
        m_ant = ant;
        m_isChanged = true;
    }
    else
    {
        LOGE("Cell[%i, %i]: can not move ant (%s)", m_pos.x(), m_pos.y(), ant->getString().c_str());
    }
}

};