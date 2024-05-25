#pragma once

#include <string>

#define CONFIG_PARAMETER(t, x, d) public: t x() const { return m_##x; } protected: t m_##x = d;

namespace WarAnts
{

class Config
{
public:
    Config();
    Config(const std::string& filename);
    virtual ~Config() = default;

    CONFIG_PARAMETER(bool, isInit, false)

    // map
    CONFIG_PARAMETER(uint32_t, width, 25)
    CONFIG_PARAMETER(uint32_t, height, 25)
    CONFIG_PARAMETER(float, stoneOnMap, 10.0f)
    CONFIG_PARAMETER(float, foodOnMap, 10.0f)
    CONFIG_PARAMETER(bool, isBounded, true)
    CONFIG_PARAMETER(uint32_t, workerCountOfStart, 5)
    CONFIG_PARAMETER(uint32_t, solderCountOfStart, 3)

    CONFIG_PARAMETER(bool, bcodeDebug, false)

    CONFIG_PARAMETER(std::string, antsFileSettings, "ants/default.json")

public:
    void setUBID(const std::string& ubid) { m_ubid = ubid; }
    const std::string& UBID() const { return m_ubid; }

protected:
    std::string m_filename;
    std::string m_ubid;
};

};
