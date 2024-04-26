#pragma once

#include <string>
#include <vector>

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

inline std::string directionToString(Direction dir, bool shortname)
{
    switch (dir)
    {
        case Direction::Nord:      return shortname ? "N"  : "Nord";
        case Direction::NordEast:  return shortname ? "NE" : "NordEast";
        case Direction::East:      return shortname ? "E"  : "East";
        case Direction::SouthEast: return shortname ? "SE" : "SouthEast";
        case Direction::South:     return shortname ? "S"  : "South";
        case Direction::SouthWest: return shortname ? "SW" : "SouthWest";
        case Direction::West:      return shortname ? "W"  : "West";
        case Direction::NordWest:  return shortname ? "NW" : "NordWest";
        default: return shortname ? "??" : "<Unknow>";
    }
}

using VectorDirection = std::vector<Direction>;

};
