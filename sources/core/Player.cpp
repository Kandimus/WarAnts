#include "Player.h"

#include "stringex.h"
#include "Log.h"

#include "../asm/asm_defines.h"
#include "wacfile.h"

#include "Ant.h"

namespace WarAnts
{

Player::Player(uint32_t index, const std::string& libname)
    : m_libName(libname)
    , m_index(index)
{
    PragmaMap pragma;
    //TODO может быть разрешить компиляцию на ходу????
    //     тогда тут нужно смотреть на расширение файла
    if (!loadWacFile(libname, m_bcode, pragma))
    {
        LOGE("Player %i: Cannot load wac file '%s'", index, libname.c_str());
        return;
    }

    m_info.antClass = pragma[Asm::PragmaType::Class];
    m_info.teamName = pragma[Asm::PragmaType::Name];
    m_info.teamVersion = pragma[Asm::PragmaType::Version];
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
