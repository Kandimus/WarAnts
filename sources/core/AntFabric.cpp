#include "AntFabric.h"

#include <fstream>
#include "nlohmann/json.hpp"
#include "Log.h"

#include "Player.h"

namespace WarAnts
{

namespace AntFabricData
{
    static std::unordered_map<std::string, std::vector<Ant>> gTemplates;
    static uint32_t gAntCount = 0;
}

bool AntFabric::init(const std::string& filename)
{
    std::ifstream file(filename);
    nlohmann::json json;

    if (!file.is_open())
    {
        return false;
    }

    file >> json;

    for (auto& [key, val] : json.items())
    {
        // нужен правильный порядок
        AntFabricData::gTemplates[key].push_back(Ant(json[key][AntTypeToString(Ant::Type::Queen)],  Ant::Type::Queen));
        AntFabricData::gTemplates[key].push_back(Ant(json[key][AntTypeToString(Ant::Type::Solder)], Ant::Type::Solder));
        AntFabricData::gTemplates[key].push_back(Ant(json[key][AntTypeToString(Ant::Type::Worker)], Ant::Type::Worker));

        LOGI("Loaded class of ant '%s'", key.c_str());
    }

    return true;
}

AntPtr AntFabric::createAnt(PlayerPtr player, Ant::Type antType)
{
    auto antClass = player->antClass();

    if (AntFabricData::gTemplates.find(antClass) == AntFabricData::gTemplates.end() ||
        antType >= Ant::Type::__MAX)
    {
        return nullptr;
    }

    auto out = std::make_shared<Ant>(AntFabricData::gTemplates[antClass][static_cast<uint8_t>(antType)]);
    out->setPlayer(player);
    out->setId(AntFabricData::gAntCount++);

    player->antIsBorn(antType);

    return out;
}

};
