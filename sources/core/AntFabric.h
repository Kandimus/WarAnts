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

    static std::shared_ptr<Ant> createAnt(std::shared_ptr<Player> player, AntType antType);
};

};
