#include "Player.h"

#include "stringex.h"
#include "Log.h"

#include "../asm/asm_defines.h"
#include "wacfile.h"

namespace WarAnts
{

Player::Player(uint32_t index, const std::string& libname)
    : m_libName(libname)
    , m_index(index)
{
    //TODO может быть разрешить компиляцию на ходу????
    //     тогда тут нужно смотреть на расширение файла
    if (!Asm::loadWacFile(libname, m_info))
    {
        LOGE("Player %i: Cannot load wac file '%s'", index, libname.c_str());
        return;
    }

    //m_info.coreVersion = atoi(pragma[Asm::PragmaType::Core].c_str());

    //TODO calc m_libHash as CRC32(file libname)
    m_libHash = 0;

    m_isInit = true;
}

Player::~Player()
{
    //if (m_fnFinalize)
    //{
    //	(*m_fnFinalize)();
    //}
}

void Player::changeTeamName(uint32_t count)
{
    m_info.teamName += " " + std::to_string(count);
}

void Player::antIsBorn(Ant::Type type)
{
    if (type >= Ant::Type::__MAX)
    {
        return;
    }

    ++m_maxCount[type];
    ++m_curCount[type];
}

void Player::antIsDied(Ant& ant)
{
    if (ant.player().get() != this)
    {
        LOGE("Error: Ant owner is not current player!");
        return;
    }

    --m_curCount[ant.type()];
    m_maxLifeCount[ant.type()] = std::max(m_maxLifeCount[ant.type()], ant.lifeCount());
    ++m_died[ant.type()];
}

void Player::addReceivedDamage(Ant::Type type, int16_t damage)
{
    if (type >= Ant::Type::__MAX)
    {
        return;
    }

    m_receivedDamage[type] += damage;
}

void Player::addDealtDamage(Ant::Type type, int16_t damage)
{
    if (type >= Ant::Type::__MAX)
    {
        return;
    }

    m_dealtDamage[type] += damage;
}

void Player::addKilled(Ant::Type type)
{
    if (type >= Ant::Type::__MAX)
    {
        return;
    }

    ++m_killed[type];
}

};
