#pragma once

#include <stdint.h>

namespace WarAnts
{

namespace Constant
{
    const float InterruptValueLow = 25.0f;
    const float InterruptValueMiddle = 50.0f;

    const int16_t DivCloseRadius = 4;
    const int16_t DivFarRadius = 2;

    const int16_t CommandRadius = 5;
    const int16_t CommandAborting = 10;

    const std::string dirConfig = "./config/";
    const std::string dirMaps = "./maps/";
    const std::string dirPlayers = "./players/";
}

}
