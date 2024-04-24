#pragma once

#include <stdint.h>
#include <string>
#include <memory>

namespace WarAnts
{
class Ant;

using AntPtr = std::shared_ptr<Ant>;

struct PlayerInfo
{
    std::string antClass = "";
    std::string teamName = "";
    std::string version = "";
//	ApiVersion apiVersion = 0;
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
    const std::string& libVersion() const { return m_info.version; }
    void changeTeamName(uint32_t count);

    void setAntQueen(const AntPtr& queen) { m_antQueen = queen; }
    AntPtr antQueen() const { return m_antQueen; }

    void modifyCountOfSolders(int32_t val) { m_countOfSolders += val; }
    uint32_t countOfSolders() const { return m_countOfSolders; }
    void modifyCountOfWorkers(int32_t val) { m_countOfWorkers += val; }
    uint32_t countOfWorkers() const { return m_countOfWorkers; }

    //AntProcess processWorker() const { return m_fnWorkerProcess; }
    //AntProcess processSolder() const { return m_fnSolderProcess; }
    //AntProcess processQueen() const { return m_fnQueenProcess; }

protected:
    bool loadFile();

protected:
    std::string m_libName = "";
    uint32_t m_libHash = 0;
    PlayerInfo m_info;
    uint32_t m_index = 0;
    bool m_isInit = false;

    //AntInit     m_fnInit = nullptr;
    //AntFinalize m_fnFinalize = nullptr;
    //AntProcess  m_fnWorkerProcess = nullptr;
    //AntProcess  m_fnSolderProcess = nullptr;
    //AntProcess  m_fnQueenProcess = nullptr;

    AntPtr m_antQueen;

    uint32_t m_countOfWorkers = 0;
    uint32_t m_countOfSolders = 0;
};

};
