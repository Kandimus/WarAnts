#pragma once

#include <stdint.h>
#include <memory>
#include <string>
#include <vector>

namespace WarAnts
{
class Ant;
enum class AntType;

using AntPtr = std::shared_ptr<Ant>;

struct PlayerInfo
{
    std::string antClass = "";
    std::string teamName = "";
    std::string teamVersion = "";
    uint16_t coreVersion = 0;
};

struct AntCount
{
    uint32_t m_all = 0;
    uint32_t m_workers = 0;
    uint32_t m_solders = 0;
    uint32_t m_queens = 0;
};

class Player
{
public:
    Player(uint32_t index, const std::string& libname);
    virtual ~Player();

    bool isInit() const { return m_isInit; }

    uint32_t index() const { return m_index; }
    const std::string& library() const { return m_libName; }
    uint32_t libHash() const { return m_libHash; }

    const std::string& antClass() const { return m_info.antClass; }
    const std::string& teamName() const { return m_info.teamName; }
    const std::string& libVersion() const { return m_info.teamVersion; }
    void changeTeamName(uint32_t count);

    void setAntQueen(const AntPtr& queen) { m_antQueen = queen; }
    AntPtr antQueen() const { return m_antQueen; }

    void antIsBorn(AntType type);
    void antIsDied(AntPtr ant);
    const AntCount& curCounts() const { return m_curCount; }
    const AntCount& maxCounts() const { return m_maxCount; }
    const AntCount& maxLifeCount() const { return m_maxLifeCount; }

protected:

protected:
    std::string m_libName = "";
    uint32_t m_libHash = 0;
    PlayerInfo m_info;
    uint32_t m_index = 0;
    bool m_isInit = false;

    std::vector<int8_t> m_bcode;

    AntPtr m_antQueen;

    // Statistic
    AntCount m_maxCount;
    AntCount m_curCount;
    AntCount m_maxLifeCount;
};

};
