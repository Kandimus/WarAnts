#pragma once

#include <stdint.h>
#include <memory>
#include <unordered_map>

#include "Ant.h"

namespace WarAnts
{

class Player;

class AntFabric
{
public:
    static bool init(const std::string& filename);

    static AntPtr createAnt(PlayerPtr player, Ant::Type antType);
};

};
