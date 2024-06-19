#include "MapMath.h"

#include <vector>
#include <algorithm>
#include <ctime>
#include <cmath>

#include "defines.h"

namespace WarAnts
{

namespace Math
{

#ifndef _WIN32
std::random_device g_randDev; //SEEEEED!!!!!!!!!!!!!!
std::mt19937 g_randGenerator(g_randDev());

std::mt19937& randGenerator()
{
    return g_randGenerator;
}

#else
SimpleRandomClass g_randGenerator;

SimpleRandomClass& randGenerator()
{
    return g_randGenerator;
}
#endif

void initRandom(uint32_t seed)
{
#ifdef _WIN32
    std::srand(seed);
#else
#endif
}

size_t random(size_t min, size_t max)
{
#ifdef _WIN32
    size_t range = max >= min ? max - min : min - max;
    if (!range) // range of one number
    {
        return max;
    }
    int r = std::rand();
    double normalize_rand = static_cast<double>(r) / RAND_MAX;
    return static_cast<size_t>(normalize_rand * range + 0.5);
#else
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
    return dist(g_randGenerator);
#endif

}

// return random direction
Direction randDirection()
{
    return static_cast<Direction>(random(0, 7));
}

//Position randomPositionByDirection(const Direction& dir, uint32_t len)
//{
//	Position result = positionOffset(dir) * len;
//	uint32_t max = len / 3;
//
//	max = !max ? 1 : max;
//
//	result.setX(result.x() + random(0, max) - len / 6);
//	result.setY(result.y() + random(0, max) - len / 6);
//
//	return result;
//}

///////////////////////////////////////////////////////////////////////////////
/// \brief return position offset to direction
Position positionOffset(const Direction& dir)
{
    Direction d = dir;

    switch(d)
    {
        case Direction::Nord:      return Position( 0, -1);
        case Direction::NordEast:  return Position( 1, -1);
        case Direction::East:      return Position( 1,  0);
        case Direction::SouthEast: return Position( 1,  1);
        case Direction::South:     return Position( 0,  1);
        case Direction::SouthWest: return Position(-1,  1);
        case Direction::West:      return Position(-1,  0);
        case Direction::NordWest:  return Position(-1, -1);
    }
    return positionOffset(randDirection());
}

///////////////////////////////////////////////////////////////////////////////
/// \brief normalize value of direction
///
/// Normalize any value to the direction enum
Direction normalizeDirection(int val)
{
    return static_cast<Direction>(val & 0x07);
}

Direction probabilisticDirection(const Direction& dir)
{
    const size_t sizeArray = 30;
    int val = static_cast<int>(dir);

    // 56.6% - move to direction
    // 20.0% - move close in direction
    // 13.3% - move perpendicular to the direction
    // 10.0% - move to reverse direction
    Direction array[sizeArray] = {
        dir, dir, dir, dir, dir,
        dir, dir, dir, dir, dir,
        dir, dir, dir, dir, dir,
        dir, dir,

        normalizeDirection(val + 1), normalizeDirection(val + 1), normalizeDirection(val + 1),
        normalizeDirection(val - 1), normalizeDirection(val - 1), normalizeDirection(val - 1),

        normalizeDirection(val + 2), normalizeDirection(val + 2),
        normalizeDirection(val - 2), normalizeDirection(val - 2),

        normalizeDirection(val + 3),
        normalizeDirection(val - 3),
        normalizeDirection(val + 4)};

    return array[random(0, sizeArray - 1)];
}

Direction directionTo(const Position& posFrom, const Position& posTo)
{
    //TODO Учитывать что карта может быть без бордюров!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if (posFrom == posTo)
    {
        return randDirection();
    }

    // convert the pointTo to coordinate system the pointFrom
    Position pos = posTo - posFrom;
    if (pos.x() == 0)
    {
        return pos.y() > 0 ? Direction::South : Direction::Nord;
    }
    if (pos.y() == 0)
    {
        return pos.x() > 0 ? Direction::East : Direction::West;
    }

    if (pos.x() > 0 && pos.y() > 0)
    {
        if (pos.x() >= 2 * pos.y())
        {
            return Direction::East;
        }

        if (pos.y() >= 2 * pos.x())
        {
            return Direction::South;
        }

        return Direction::SouthEast;
    }

    if (pos.x() < 0 && pos.y() > 0)
    {
        auto abs_x = std::abs(pos.x());
        if (abs_x >=  2 * pos.y())
        {
            return Direction::West;
        }

        if (pos.y() >= 2 * abs_x)
        {
            return Direction::South;
        }

        return Direction::SouthWest;
    }

    if (pos.x() > 0 && pos.y() < 0)
    {
        auto abs_y = std::abs(pos.y());
        if (pos.x() >= 2 * abs_y)
        {
            return Direction::East;
        }

        if (abs_y >= 2 * pos.x())
        {
            return Direction::Nord;
        }

        return Direction::NordEast;
    }

    if (pos.x() < 0 && pos.y() < 0)
    {
        auto abs_x = std::abs(pos.x());
        auto abs_y = std::abs(pos.y());
        if (abs_x >= 2 * abs_y)
        {
            return Direction::West;
        }

        if (abs_y >= 2 * abs_x)
        {
            return Direction::Nord;
        }

        return Direction::NordWest;
    }

    SU_BREAKPOINT();
    return randDirection();
}

//TODO Need optimize this algorithm!!!!!!!!!!
uint32_t distanceTo(const Position& posFrom, const Position& posTo)
{
    Position pos = posTo - posFrom;
    return static_cast<uint32_t>(std::sqrt(double(pos.x()) * double(pos.x()) + double(pos.y()) * double(pos.y())) + 0.5);
}

/// \brief Create the priority array of direction.
///
/// The array will sorted by priority of select direction, from selected to reverse direction.
/// Middle values will added by random order (clockwise or counter-clockwise)
VectorDirection createDirectionArray(const Direction& dir)
{
    std::vector<Direction> array;
    int clockwise = (int)random(0, 1);
    int val = static_cast<int>(dir);

    array.push_back(dir);
    array.push_back(normalizeDirection(clockwise ? val + 1 : val - 1));
    array.push_back(normalizeDirection(clockwise ? val - 1 : val + 1));
    array.push_back(normalizeDirection(clockwise ? val + 2 : val - 2));
    array.push_back(normalizeDirection(clockwise ? val - 2 : val + 2));
    array.push_back(normalizeDirection(clockwise ? val + 3 : val - 3));
    array.push_back(normalizeDirection(clockwise ? val - 3 : val + 3));
    array.push_back(normalizeDirection(val + 4));

    return array;
}

//Direction inverseDirection(const Direction& dir)
//{
//	switch(dir) {
//		case Direction::Nord:      return Direction::South;
//		case Direction::NordEast:  return Direction::SouthWest;
//		case Direction::East:      return Direction::West;
//		case Direction::SouthEast: return Direction::NordWest;
//		case Direction::South:     return Direction::Nord;
//		case Direction::SouthWest: return Direction::NordEast;
//		case Direction::West:      return Direction::East;
//		case Direction::NordWest:  return Direction::SouthEast;
//		default: return randDirection();
//	}
//}

//TODO Need optimize this algorithm!!!!!!!!!!
VectorPosition visibleCells(const Position& pos, int16_t visibility)
{
    std::vector<Position> result;

    if (visibility <= 0)
    {
        result.push_back(pos);
        return result;
    }

    size_t side = 2 * visibility + 1;
    result.reserve(side * side);

    if (visibility == 1)
    {
        result.push_back(pos + Position(-1, -1));
        result.push_back(pos + Position( 0, -1));
        result.push_back(pos + Position( 1, -1));
        result.push_back(pos + Position(-1,  0));
        result.push_back(pos + Position( 0,  0));
        result.push_back(pos + Position( 1,  0));
        result.push_back(pos + Position(-1,  1));
        result.push_back(pos + Position( 0,  1));
        result.push_back(pos + Position( 1,  1));
        return result;
    }

    int dim_fill_square = static_cast<int>(std::sqrt(double(visibility) * double(visibility) / 2.0) + 0.5);

    for (int y = -dim_fill_square; y <= dim_fill_square; ++y)
    {
        for (int x = -dim_fill_square; x <= dim_fill_square; ++x)
        {
            result.push_back(pos + Position(x, y));
        }
    }

    for (int y = -visibility; y < -dim_fill_square; ++y)
    {
        auto yy = double(y) * double(y);

        for (int x = -visibility; x <= visibility; ++x)
        {
            int r = static_cast<int16_t>(std::sqrt(double(x) * double(x) + yy) + 0.5);

            if (r <= visibility)
            {
                result.push_back(pos + Position(x, y));
            }
        }
    }

    for (int y = dim_fill_square + 1; y <= visibility; ++y)
    {
        for (int x = -visibility; x <= visibility; ++x)
        {
            int r = static_cast<int16_t>(std::sqrt(double(x) * double(x) + double(y) * double(y)) + 0.5);

            if (r <= visibility)
            {
                result.push_back(pos + Position(x, y));
            }
        }
    }

    for (int x = -visibility; x < -dim_fill_square; ++x)
    {
        for (int y = -dim_fill_square + 1; y <= dim_fill_square - 1; ++y)
        {
            int r = static_cast<int>(std::sqrt(double(x) * double(x) + double(y) * double(y)) + 0.5);

            if (r <= visibility)
            {
                result.push_back(pos + Position(x, y));
            }
        }
    }

    for (int x = dim_fill_square + 1; x <= visibility; ++x)
    {
        for (int y = -dim_fill_square + 1; y <= dim_fill_square - 1; ++y)
        {
            int r = static_cast<int>(std::sqrt(double(x) * double(x) + double(y) * double(y)) + 0.5);

            if (r <= visibility)
            {
                result.push_back(pos + Position(x, y));
            }
        }
    }

    //std::sort(result.begin(), result.end(), [](const Position& a, const Position& b)
    //{
    //    int64_t v1 = a.y();
    //    int64_t v2 = b.y();

    //    v1 = (v1 << 32) + a.x();
    //    v2 = (v2 << 32) + b.x();
    //    return v1 < v2;
    //});

    return result;
}

}; // namespace Math

}; // namespace WarAnts
