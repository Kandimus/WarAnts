#pragma once

#include <stdint.h>
#include <random>

#include "Direction.h"
#include "Position.h"

//#include "AntInfo.h"

namespace WarAnts
{

namespace Math
{

void initRandom(uint32_t seed);
size_t random(size_t min, size_t max);

#ifndef _WIN32
std::mt19937& randGenerator();
#else
class SimpleRandomClass
{
public:
    typedef size_t result_type;
    static size_t min() { return 0; }
    static size_t max() { return RAND_MAX; }
    size_t operator()() { return random(min(), max()); }
};

SimpleRandomClass& randGenerator();
#endif

Direction randDirection();
Direction normalizeDirection(int val);
//
Direction directionTo(const Position& posFrom, const Position& posTo);
uint32_t distanceTo(const Position& posFrom, const Position& posTo);
//
//Position randomPositionByDirection(const Direction& dir, uint32_t len);

Position positionOffset(const Direction& dir);
//
VectorDirection createDirectionArray(const Direction& dir);
Direction probabilisticDirection(const Direction& dir);
//Direction inverseDirection(const Direction& dir);
VectorPosition visibleCells(const Position& pos, int16_t visibility);
//
//std::string descriptionDirection(const Direction& dir, bool shortname = false);

};

};
