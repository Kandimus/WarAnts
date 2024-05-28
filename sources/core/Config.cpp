#include "Config.h"
#include <fstream>

#include "jsonhelper.h"

namespace WarAnts
{

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
    file.close();

    m_width = JsonHelper::getValue2<uint32_t>(json, "map", "width", m_width, 15, 1000);
    m_height = JsonHelper::getValue2<uint32_t>(json, "map", "height", m_height, 15, 1000);
    m_stoneOnMap = JsonHelper::getValue2<float>(json, "map", "stone", m_stoneOnMap, 0, 50);
    m_foodOnMap = JsonHelper::getValue2<float>(json, "map", "food", m_foodOnMap, 0, 45);
    m_isBounded = JsonHelper::getValue2<bool>(json, "map", "borders", m_isBounded, false, true);
    m_workerCountOfStart = JsonHelper::getValue2<uint32_t>(json, "map", "worker_count", m_workerCountOfStart, 1, 0x7fff);
    m_solderCountOfStart = JsonHelper::getValue2<uint32_t>(json, "map", "solder_count", m_solderCountOfStart, 1, 0x7fff);

    m_antsFileSettings = JsonHelper::getValue1<std::string>(json, "ants", m_antsFileSettings);

    m_bcodeDebug = JsonHelper::getValue2<bool>(json, "bcode", "debug", m_bcodeDebug);

    m_isInit = true;
}

};
