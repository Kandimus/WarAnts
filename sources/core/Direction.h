#pragma once

#include <string>

namespace WarAnts
{

enum class Direction
{
    Nord = 0,
    NordEast,
    East,
    SouthEast,
    South,
    SouthWest,
    West,
    NordWest,
};

inline std::string directionToString(Direction dir)
{
    switch (dir)
    {
        case WarAnts::Direction::Nord: return "N";
        case WarAnts::Direction::NordEast: return "NE";
        case WarAnts::Direction::East: return "E";
        case WarAnts::Direction::SouthEast:  return "SE";
        case WarAnts::Direction::South: return "S";
        case WarAnts::Direction::SouthWest: return "SW";
        case WarAnts::Direction::West: return "W";
        case WarAnts::Direction::NordWest: return "NW";
        default: return "?";
    }
}


};
