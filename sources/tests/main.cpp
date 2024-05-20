﻿//#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include <fstream>

#include "cell.h"
#include "Compiler.h"
#include "config.h"
#include "log.h"
#include "Map.h"
#include "memory.h"
#include "MapMath.h"
#include "Player.h"
#include "VirtualMachine.h"

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

class TestPlayer : public WarAnts::Player
{
public:
    TestPlayer(const WarAnts::Asm::WacFile& wac) : WarAnts::Player(0, "")
    {
        m_info = wac;
    }
};

class TestAnt : public WarAnts::Ant
{
public:
    TestAnt(const std::shared_ptr<TestPlayer>& plr) : WarAnts::Ant()
    {
        m_type = WarAnts::AntType::Worker;
        m_visibility = 1;
        m_player = plr;
        m_memory.resize(WarAnts::Memory::UserData + 256);
    }
};

int main(int argc, char* argv[])
{
    su::Log::instance().setFile(false);
    su::Log::instance().setTerminal(false);

    return Catch::Session().run(argc, argv);
}


void PrintVisibleArr(const WarAnts::VectorPosition& arr, const WarAnts::Position& pos, const std::string& filename)
{
    std::string out = "";

    for (int y = 0; y < 27; ++y)
    {
        for (int x = 0; x < 27; ++x)
        {
            bool found = false;
            for (const auto& item : arr)
            {
                if (item == WarAnts::Position(x, y))
                {
                    found = true;
                    break;
                }
            }

            out += (WarAnts::Position(x, y) == pos) ? '*' : (found ? 'X' : ' ');
        }
        out += "\n";
    }

    std::ofstream file(filename);
    if (file.is_open())
    {
        file << out;
        file.close();
    }
}

std::shared_ptr<TestAnt> runBCode(const std::string& filename)
{
    WarAnts::Asm::WacFile wac;
    StringArray errors;
    StringArray warnings;
    auto result = WarAnts::Asm::compileFile("./tests/" + filename, warnings, errors, wac);

    REQUIRE(errors.empty());

    std::shared_ptr<TestPlayer> plr = std::make_shared<TestPlayer>(wac);
    std::shared_ptr<TestAnt> ant = std::make_shared<TestAnt>(plr);
    std::shared_ptr<PublicMap> map = std::make_shared<PublicMap>();

    WarAnts::VirtualMachine vm(map, ant);

    vm.run();

    return ant;
}

TEST_CASE("visibleCells", "[Math]")
{
    WarAnts::Position center(12, 12);

    for (int vis = 0; vis < 13; ++vis)
    {

        auto arr = WarAnts::Math::visibleCells(center, vis);
        PrintVisibleArr(arr, center, su::String_format2("./tests/visible_%02i.txt", vis));
    }
}

TEST_CASE("directionTo", "[Math]")
{
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(1, 1), WarAnts::Position(0, 19)) == WarAnts::Direction::South);

    CHECK(WarAnts::Math::directionTo(WarAnts::Position(6, 6), WarAnts::Position( 6,  0)) == WarAnts::Direction::Nord);
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(6, 6), WarAnts::Position( 9,  0)) == WarAnts::Direction::Nord);
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(6, 6), WarAnts::Position(10,  0)) == WarAnts::Direction::NordEast);
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(6, 6), WarAnts::Position(12,  0)) == WarAnts::Direction::NordEast);
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(6, 6), WarAnts::Position(12,  2)) == WarAnts::Direction::NordEast);
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(6, 6), WarAnts::Position(12,  3)) == WarAnts::Direction::East);
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(6, 6), WarAnts::Position(12,  6)) == WarAnts::Direction::East);
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(6, 6), WarAnts::Position(12,  9)) == WarAnts::Direction::East);
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(6, 6), WarAnts::Position(12, 10)) == WarAnts::Direction::SouthEast);
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(6, 6), WarAnts::Position(12, 12)) == WarAnts::Direction::SouthEast);
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(6, 6), WarAnts::Position(10, 12)) == WarAnts::Direction::SouthEast);
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(6, 6), WarAnts::Position( 9, 12)) == WarAnts::Direction::South);
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(6, 6), WarAnts::Position( 6, 12)) == WarAnts::Direction::South);
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(6, 6), WarAnts::Position( 3, 12)) == WarAnts::Direction::South);
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(6, 6), WarAnts::Position( 2, 12)) == WarAnts::Direction::SouthWest);
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(6, 6), WarAnts::Position( 0, 12)) == WarAnts::Direction::SouthWest);
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(6, 6), WarAnts::Position( 0, 10)) == WarAnts::Direction::SouthWest);
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(6, 6), WarAnts::Position( 0,  9)) == WarAnts::Direction::West);
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(6, 6), WarAnts::Position( 0,  6)) == WarAnts::Direction::West);
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(6, 6), WarAnts::Position( 0,  3)) == WarAnts::Direction::West);
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(6, 6), WarAnts::Position( 0,  2)) == WarAnts::Direction::NordWest);
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(6, 6), WarAnts::Position( 0,  0)) == WarAnts::Direction::NordWest);
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(6, 6), WarAnts::Position( 2,  0)) == WarAnts::Direction::NordWest);
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(6, 6), WarAnts::Position( 3,  0)) == WarAnts::Direction::Nord);

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

TEST_CASE("basic", "[VM]")
{
    auto ant = runBCode("basic.wasm");
    CHECK(ant->getValue(48) == 48);
    CHECK(ant->getValue(49) == 49);
    CHECK(ant->getValue(50) == 50);
}

TEST_CASE("arithmetic", "[VM]")
{
    auto ant = runBCode("arithmetic.wasm");
    CHECK(ant->getValue(48) == 11);
    CHECK(ant->getValue(49) == 1);
}

TEST_CASE("min", "[VM]")
{
    auto ant = runBCode("min.wasm");
    CHECK(ant->getValue(48) == 7);
    CHECK(ant->getValue(49) == 1);
}

TEST_CASE("max", "[VM]")
{
    auto ant = runBCode("max.wasm");
    CHECK(ant->getValue(48) == 7);
    CHECK(ant->getValue(49) == 1);
}

TEST_CASE("bit", "[VM]")
{
    auto ant = runBCode("bit.wasm");
    CHECK(ant->getValue(48) == 16);
    CHECK(ant->getValue(49) == 1);
    CHECK(ant->getValue(50) == 0x0170);
}

