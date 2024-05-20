#include "Config.h"
#include <fstream>

namespace WarAnts
{

template<typename T>
static T getJsonValue1(const nlohmann::json& json, const std::string& param, const T& defval)
{
    return json.contains(param)
        ? static_cast<T>(json[param])
        : defval;
}

template<typename T>
static T getJsonValue2(const nlohmann::json& json, const std::string& folder, const std::string& param, const T& defval)
{
    return (json.contains(folder) && json[folder].contains(param))
        ? static_cast<T>(json[folder][param])
        : defval;
}

Config::Config()
{
    m_isInit = true;
}

Config::Config(const std::string& filename) : m_filename(filename)
{
    std::ifstream file(filename);
    nlohmann::json json;

    if (!file.is_open())
    {
        return;
    }

    file >> json;

    m_width = getJsonValue2<uint32_t>(json, "map", "width", m_width);
    m_height = getJsonValue2<uint32_t>(json, "map", "height", m_height);
    m_stoneOnMap = getJsonValue2<float>(json, "map", "stone", m_stoneOnMap);
    m_foodOnMap = getJsonValue2<float>(json, "map", "food", m_foodOnMap);
    m_isBounded = getJsonValue2<bool>(json, "map", "borders", m_isBounded);
    m_workerCountOfStart = getJsonValue2<uint32_t>(json, "map", "worker_count", m_workerCountOfStart);
    m_solderCountOfStart = getJsonValue2<uint32_t>(json, "map", "solder_count", m_solderCountOfStart);

    m_antsFileSettings = getJsonValue1<std::string>(json, "ants", m_antsFileSettings);

    m_isInit = true;
}

};
