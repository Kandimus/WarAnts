#include "Player.h"

#include "stringex.h"
#include "Log.h"

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

};
