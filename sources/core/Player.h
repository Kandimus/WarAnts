#pragma once

#include <stdint.h>
#include <memory>
#include <string>
#include <vector>

#include "AntDefinition.h"
#include "wacfile.h"

namespace WarAnts
{
class Ant;
using AntPtr = std::shared_ptr<Ant>;

class Player
{
public:
    enum Status
    {
        InGame = 0,
        Lost,
    };

    Player(uint32_t index, const std::string& libname);
    virtual ~Player();

    bool isInit() const { return m_isInit; }

    uint32_t index() const { return m_index; }
    const std::string& library() const { return m_libName; }
    uint32_t libHash() const { return m_libHash; }

    const std::string& antClass() const { return m_info.teamClass; }
    const std::string& teamName() const { return m_info.teamName; }
    const std::string& libVersion() const { return m_info.teamVersion; }
    void changeTeamName(uint32_t count);

    void setAntQueen(const AntPtr& queen) { m_antQueen = queen; }
    AntPtr antQueen() const { return m_antQueen; }

    // statistic
    void antIsBorn(AntDefinition::Type type);
    void antIsDied(Ant& ant);
    void addReceivedDamage(AntDefinition::Type type, int16_t damage);
    void addDealtDamage(AntDefinition::Type type, int16_t damage);
    void addKilled(AntDefinition::Type type);

    // wac
    const Asm::WacFile& info() const { return m_info; }

protected:

protected:
    std::string m_libName = "";
    uint32_t m_libHash = 0;
    Asm::WacFile m_info;
    uint32_t m_index = 0;
    bool m_isInit = false;
    Status m_status = Status::InGame;

    AntPtr m_antQueen;

    // Statistic
    uint32_t m_maxCount[AntDefinition::Type::__MAX];
    uint32_t m_curCount[AntDefinition::Type::__MAX];
    uint32_t m_maxLifeCount[AntDefinition::Type::__MAX];
    uint32_t m_receivedDamage[AntDefinition::Type::__MAX];
    uint32_t m_dealtDamage[AntDefinition::Type::__MAX];
    uint32_t m_killed[AntDefinition::Type::__MAX];
    uint32_t m_died[AntDefinition::Type::__MAX];
};

};
