#include "Player.h"

#include "stringex.h"
#include "Log.h"

#include "Ant.h"

namespace WarAnts
{

Player::Player(uint32_t index, const std::string& libname)
    : m_libName(libname)
    , m_index(index)
{
    //load lib
    if (loadFile())
    {
        // get PlayerInfo
        //(*m_fnInit)(&m_info);
        m_isInit = true;
    }

    //TODO calc m_libHash as CRC32(file libname)
    m_libHash = 0;
}

Player::~Player()
{
    //if (m_fnFinalize)
    //{
    //	(*m_fnFinalize)();
    //}
}

bool Player::loadFile()
{
    std::string filename = "./players/" + m_libName;
    //TODO load asm file and compile it

    m_info.antClass = "black";
    m_info.teamName = "Test team";
    m_info.version = "1.0";

    return true;
}

void Player::changeTeamName(uint32_t count)
{
    m_info.teamName += " " + std::to_string(count);
}

void Player::antIsBorn(AntType type)
{
    switch (type)
    {
        case AntType::Queen:
            ++m_maxCount.m_all;
            ++m_maxCount.m_queens;
            ++m_curCount.m_all;
            ++m_curCount.m_queens;
            break;

        case AntType::Solder:
            ++m_maxCount.m_all;
            ++m_maxCount.m_solders;
            ++m_curCount.m_all;
            ++m_curCount.m_solders;
            break;

        case AntType::Worker:
            ++m_maxCount.m_all;
            ++m_maxCount.m_workers;
            ++m_curCount.m_all;
            ++m_curCount.m_workers;
            break;

        default: break;
    }
}

void Player::antIsDied(AntPtr ant)
{
    if (ant->player().get() != this)
    {
        LOGE("Error: Ant owner is not current player!");
        return;
    }

    switch (ant->type())
    {
        case AntType::Queen:
            --m_curCount.m_all;
            --m_curCount.m_queens;
            m_maxLifeCount.m_queens = std::max(m_maxLifeCount.m_queens, ant->lifeCount());
            m_maxLifeCount.m_all = std::max(m_maxLifeCount.m_all, ant->lifeCount());
            break;

        case AntType::Solder:
            --m_curCount.m_all;
            --m_curCount.m_solders;
            m_maxLifeCount.m_solders = std::max(m_maxLifeCount.m_solders, ant->lifeCount());
            m_maxLifeCount.m_all = std::max(m_maxLifeCount.m_all, ant->lifeCount());
            break;

        case AntType::Worker:
            --m_curCount.m_all;
            --m_curCount.m_workers;
            m_maxLifeCount.m_workers = std::max(m_maxLifeCount.m_workers, ant->lifeCount());
            m_maxLifeCount.m_all = std::max(m_maxLifeCount.m_all, ant->lifeCount());
            break;

        default: break;
    }


}

};
