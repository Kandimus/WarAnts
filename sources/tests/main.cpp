#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Map.h"
#include "MapMath.h"
#include "log.h"
#include "config.h"
#include "cell.h"

class PublicMap : public WarAnts::Map
{
public:
    PublicMap() : WarAnts::Map(std::make_shared<WarAnts::Config>())
    {
        createMap(15, 15);
    }

    inline WarAnts::Cell* getCell(int x, int y)
    {
        return m_map[absPosition(WarAnts::Position(x, y))].get();
    }
};

TEST_CASE("directionTo", "[Math]")
{
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(1, 1), WarAnts::Position(0, 19)) == WarAnts::Direction::South);
}

TEST_CASE("nearAvaliblePosition", "[Map]")
{
    PublicMap map;

    for (int xx = -2; xx <= 2; ++xx)
    {
        for (int yy = -2; yy <= 2; ++yy)
        {
            map.getCell(7 + xx, 7 + yy)->setStone(true);
        }
    }

    /*
      X X X X X
      X X X X X
      X X[X]X X
      X X X + X
      X X X X X
    */
    map.getCell(8, 8)->setStone(false);
    auto pos1 = map.nearAvaliblePosition(WarAnts::Position(7, 7));
    CHECK(pos1 == WarAnts::Position(8, 8));

    /*
      X X X + X
      X X X X X
      X X[X]X X
      X X X X X
      X X + X X
    */
    map.getCell(8, 8)->setStone(true);
    map.getCell(8, 5)->setStone(false);
    map.getCell(7, 9)->setStone(false);

    int test2a = 0;
    int test2b = 0;
    int test2max = 10;
    for (int ii = 0; ii < test2max; ++ii)
    {
        auto pos2 = map.nearAvaliblePosition(WarAnts::Position(7, 7));

        test2a += pos2 == WarAnts::Position(8, 5);
        test2b += pos2 == WarAnts::Position(7, 9);
    }

    CHECK(test2a);
    CHECK(test2b);
    CHECK((test2a + test2b) == test2max);
}

