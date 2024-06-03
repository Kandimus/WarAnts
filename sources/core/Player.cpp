#include "Player.h"

#include "stringex.h"
#include "Log.h"

#include "asm_defines.h"
#include "Compiler.h"
#include "wacfile.h"

namespace WarAnts
{

Player::Player(uint32_t index, const std::string& libname)
    : m_libName(libname)
    , m_index(index)
{
    std::string ext = su::String_extensionFilename(m_libName);

    if (ext == "wasm")
    {
        StringArray errors;
        StringArray warnings;

        LOGI("Player %i: compile the source asm file '%s'...", index, libname.c_str());

        auto result = Asm::compileFile(libname, warnings, errors, m_info);

        if (errors.size())
        {
            LOGE("Player %i: compiler errors...");
            for (const auto& str : errors)
            {
                LOGE(str.c_str());
            }
            return;
        }

        if (warnings.size())
        {
            LOGE("Player %i: compiler warnings...");
            for (const auto& str : warnings)
            {
                LOGW(str.c_str());
            }
        }
    }
    else if (ext == "wac")
    {
        LOGI("Player %i: load the compiled asm file '%s'...", index, libname.c_str());

        if (!Asm::loadWacFile(libname, m_info))
        {
            LOGE("Player %i: Cannot load wac file '%s'", index, libname.c_str());
            return;
        }
    }
    else
    {
        LOGE("Player %i: Unknown extension '%s'", index, ext.c_str());
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
