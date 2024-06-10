//#define CATCH_CONFIG_MAIN
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

class TestConfig : public WarAnts::Config
{
public:
    TestConfig() : WarAnts::Config()
    {
        setUBID("test");
        m_bcodeDebug = true;
    }

    void setBounded(bool bounded) { m_isBounded = bounded; }
};

class PublicMap : public WarAnts::Map
{
public:
    PublicMap() : WarAnts::Map(std::make_shared<TestConfig>(), "")
    {
        setSize(15, 15);
        createMap();
    }

    inline void setBounded(bool bounded)
    {
        return dynamic_cast<TestConfig*>(m_conf.get())->setBounded(bounded);
    }

    inline WarAnts::Cell* getCell(int x, int y)
    {
        return m_map[absPosition(WarAnts::Position(x, y))].get();
    }

    inline void setAnt(WarAnts::AntPtr ant)
    {
        REQUIRE(isValidPosition(ant->position()));
        
        auto cell = m_map[absPosition(ant->position())];
        cell->setAnt(ant.get());
    }
};

class TestPlayer : public WarAnts::Player
{
public:
    TestPlayer(const WarAnts::Asm::WacFile& wac) : WarAnts::Player(0, "")
    {
        m_info = wac;
    }

    void setLibname(const std::string& filename)
    {
        m_libName = filename;
    }
};

class TestAnt : public WarAnts::Ant
{
public:
    TestAnt(WarAnts::Ant::Type type, int16_t x, int16_t y, const std::shared_ptr<TestPlayer>& plr) : WarAnts::Ant()
    {
        m_pos = WarAnts::Position(x, y);
        m_type = type;
        m_maxHealth = 100;
        m_health = 100;
        m_visibility = 5;
        m_player = plr;
        m_memory.resize(WarAnts::Memory::UserData + 0x70);
    }

    void setType(WarAnts::Ant::Type type) { m_type = type; }
    void setHealth(int16_t health) { m_health = health; }
    void setSatiety(int16_t v) { m_satiety = v; }
    void setCargo(int16_t v) { m_cargo = v; }
    void setMaxSatiety(int16_t v) { m_maxSatiety = v; }
    void setMaxCargo(int16_t v) { m_maxCargo = v; }
    void setFoodPerTurn(int16_t v) { m_foodPerTurn = v; }
};

int main(int argc, char* argv[])
{
    su::Log::instance().setFile(true);
    su::Log::instance().setDir("logs");
    su::Log::instance().setFilename("test");
    su::Log::instance().setLevel(su::Log::Level::Error);
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

            out += (WarAnts::Position(x, y) == pos) ? '¤' : (found ? 'X' : '·');
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

/*

   0123456789ABCDE
  +---------------+
 0|·S··F··X       |
 1|··C·····       |
 2|··¤·····     f |
 3|··X····W      x|
 4|········       |
 5|F······     Q  |
 6|···Z···        |
 7| ···Ff         |
 8|               |
 9|   x           |
 A|         w     |
 B|               |
 C|  f         f  |
 D|               |
 E|     C         |
  +---------------+

*/

std::shared_ptr<TestAnt> runBCode(bool isBounded, const std::string& filename)
{
    WarAnts::Asm::WacFile wac;
    WarAnts::Asm::WacFile wacEnemy;
    StringArray errors;
    StringArray warnings;
    auto result = WarAnts::Asm::compileFile("./tests/" + filename, warnings, errors, wac);

    REQUIRE(errors.empty());

    // main player
    std::shared_ptr<TestPlayer> plr = std::make_shared<TestPlayer>(wac);
    plr->setLibname(filename);

    // Allies
    std::shared_ptr<TestAnt> qAlly_1 = std::make_shared<TestAnt>(WarAnts::Ant::Type::Queen, 12, 5, plr);
    std::shared_ptr<TestAnt> sAlly_1 = std::make_shared<TestAnt>(WarAnts::Ant::Type::Solder, 1, 0, plr);
    std::shared_ptr<TestAnt> wAlly_1 = std::make_shared<TestAnt>(WarAnts::Ant::Type::Worker, 7, 3, plr);
    std::shared_ptr<TestAnt> wAlly_2 = std::make_shared<TestAnt>(WarAnts::Ant::Type::Worker, 9, 10, plr);
    sAlly_1->setHealth(50);

    // Enemies
    std::shared_ptr<TestPlayer> plrEnemy = std::make_shared<TestPlayer>(wacEnemy);
    std::shared_ptr<TestAnt> qEnemy_1 = std::make_shared<TestAnt>(WarAnts::Ant::Type::Queen, 3, 6, plrEnemy);
    std::shared_ptr<TestAnt> sEnemy_1 = std::make_shared<TestAnt>(WarAnts::Ant::Type::Solder, 7, 0, plrEnemy);
    std::shared_ptr<TestAnt> sEnemy_2 = std::make_shared<TestAnt>(WarAnts::Ant::Type::Solder, 14, 3, plrEnemy);
    std::shared_ptr<TestAnt> sEnemy_3 = std::make_shared<TestAnt>(WarAnts::Ant::Type::Solder, 2, 3, plrEnemy);
    std::shared_ptr<TestAnt> sEnemy_4 = std::make_shared<TestAnt>(WarAnts::Ant::Type::Solder, 3, 9, plrEnemy);
    std::shared_ptr<TestAnt> wEnemy_1 = std::make_shared<TestAnt>(WarAnts::Ant::Type::Worker, 2, 1, plrEnemy);
    std::shared_ptr<TestAnt> wEnemy_2 = std::make_shared<TestAnt>(WarAnts::Ant::Type::Worker, 5, 14, plrEnemy);
    qEnemy_1->setHealth(75);
    sEnemy_3->setHealth(25);

    // The ant!
    std::shared_ptr<TestAnt> ant = std::make_shared<TestAnt>(WarAnts::Ant::Type::Worker, 2, 2, plr);

    // Map
    std::shared_ptr<PublicMap> map = std::make_shared<PublicMap>();
    map->setBounded(isBounded);

    map->getCell( 4,  0)->modifyFood(100);
    map->getCell(13,  2)->modifyFood(50);
    map->getCell( 0,  5)->modifyFood(75);
    map->getCell( 5,  7)->modifyFood(10);
    map->getCell( 4,  7)->modifyFood(20);
    map->getCell( 2, 12)->modifyFood(250);
    map->getCell(12, 12)->modifyFood(1000);

    map->setAnt(ant);
    map->setAnt(qAlly_1);
    map->setAnt(sAlly_1);
    map->setAnt(wAlly_1);
    map->setAnt(wAlly_2);

    map->setAnt(qEnemy_1);
    map->setAnt(sEnemy_1);
    map->setAnt(sEnemy_2);
    map->setAnt(sEnemy_3);
    map->setAnt(sEnemy_4);
    map->setAnt(wEnemy_1);
    map->setAnt(wEnemy_2);

    WarAnts::VirtualMachine vm(0, map, ant);

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
    CHECK(WarAnts::Math::directionTo(WarAnts::Position(45, 22), WarAnts::Position(43, 22)) == WarAnts::Direction::West);

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
    auto pos1 = map.closestAvaliblePosition(WarAnts::Position(7, 7));
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
        auto pos2 = map.closestAvaliblePosition(WarAnts::Position(7, 7));

        test2a += pos2 == WarAnts::Position(8, 5);
        test2b += pos2 == WarAnts::Position(7, 9);
    }

    CHECK(test2a);
    CHECK(test2b);
    CHECK((test2a + test2b) == test2max);
}

TEST_CASE("takeFood", "[Map]")
{
    WarAnts::Asm::WacFile wac;
    std::shared_ptr<TestPlayer> plr = std::make_shared<TestPlayer>(wac);
    plr->setLibname("---");

    // The ant
    std::shared_ptr<TestAnt> ant = std::make_shared<TestAnt>(WarAnts::Ant::Type::Worker, 2, 2, plr);
    ant->setFoodPerTurn(15);
    ant->setMaxCargo(30);
    ant->clearCargo();

    // Map
    std::shared_ptr<PublicMap> map = std::make_shared<PublicMap>();
    map->setBounded(true);
    map->getCell(1, 1)->modifyFood(20);
    map->getCell(3, 3)->modifyFood(50);

    // 
    int16_t food = map->takeFood(WarAnts::Position(1, 1), *ant, true);
    ant->modifyCargo(food);

    CHECK(food == 15);
    CHECK(ant->cargo() == 15);
    CHECK(int16_t(ant->cargoPercent() * 10) == 500);
    CHECK(map->getCell(1, 1)->food() == 5);

    // 
    food = map->takeFood(WarAnts::Position(1, 1), *ant, true);
    ant->modifyCargo(food);

    CHECK(food == 5);
    CHECK(ant->cargo() == 20);
    CHECK(int16_t(ant->cargoPercent() * 10) == 666);
    CHECK(map->getCell(1, 1)->food() == 0);

    // 
    food = map->takeFood(WarAnts::Position(3, 3), *ant, true);
    ant->modifyCargo(food);

    CHECK(food == 10);
    CHECK(ant->cargo() == 30);
    CHECK(int16_t(ant->cargoPercent() * 10) == 1000);
    CHECK(map->getCell(3, 3)->food() == 40);

    //
    food = map->takeFood(WarAnts::Position(3, 3), *ant, true);
    CHECK(food == -1);
    CHECK(ant->cargo() == 30);
    CHECK(int16_t(ant->cargoPercent() * 10) == 1000);
    CHECK(map->getCell(3, 3)->food() == 40);
}

TEST_CASE("feed", "[Map]")
{
    WarAnts::Asm::WacFile wac;
    std::shared_ptr<TestPlayer> plr = std::make_shared<TestPlayer>(wac);
    plr->setLibname("---");

    // The ant
    std::shared_ptr<TestAnt> ant = std::make_shared<TestAnt>(WarAnts::Ant::Type::Worker, 2, 2, plr);
    ant->setFoodPerTurn(20);
    ant->setMaxSatiety(150);
    ant->setSatiety(30);
    ant->setMaxCargo(5);

    // Map
    std::shared_ptr<PublicMap> map = std::make_shared<PublicMap>();
    map->setBounded(true);
    map->getCell(1, 1)->modifyFood(20);
    map->getCell(3, 3)->modifyFood(50);

    // 
    int16_t food = map->takeFood(WarAnts::Position(1, 1), *ant, false);
    ant->eat(food);

    CHECK(food == 20);
    CHECK(ant->satiety() == 50);
    CHECK(int16_t(ant->satietyPercent() * 10) == 333);
    CHECK(map->getCell(1, 1)->food() == 0);

    // 
    ant->setSatiety(140);
    food = map->takeFood(WarAnts::Position(3, 3), *ant, false);
    ant->eat(food);

    CHECK(food == 10);
    CHECK(ant->satiety() == 150);
    CHECK(int16_t(ant->satietyPercent() * 10) == 1000);
    CHECK(map->getCell(3, 3)->food() == 40);
}

TEST_CASE("eat", "[Map]")
{
    WarAnts::Asm::WacFile wac;
    std::shared_ptr<TestPlayer> plr = std::make_shared<TestPlayer>(wac);
    plr->setLibname("---");

    // The ant
    std::shared_ptr<TestAnt> ant = std::make_shared<TestAnt>(WarAnts::Ant::Type::Worker, 2, 2, plr);
    ant->setFoodPerTurn(20);
    ant->setMaxSatiety(60);
    ant->setSatiety(30);
    ant->setMaxCargo(50);
    ant->setCargo(50);

    ant->eatFromCargo();

    CHECK(ant->satiety() == 50);
    CHECK(int16_t(ant->satietyPercent() * 10) == 833);
    CHECK(ant->cargo() == 30);
    CHECK(int16_t(ant->cargoPercent() * 10) == 600);

    // 
    ant->eatFromCargo();

    CHECK(ant->satiety() == 60);
    CHECK(int16_t(ant->satietyPercent() * 10) == 1000);
    CHECK(ant->cargo() == 20);
    CHECK(int16_t(ant->cargoPercent() * 10) == 400);
}

TEST_CASE("cater", "[Map]")
{
    WarAnts::Asm::WacFile wac;
    std::shared_ptr<TestPlayer> plr = std::make_shared<TestPlayer>(wac);
    plr->setLibname("---"); 

    // The ant
    std::shared_ptr<TestAnt> ant = std::make_shared<TestAnt>(WarAnts::Ant::Type::Worker, 2, 2, plr);
    ant->setFoodPerTurn(20);
    ant->setMaxSatiety(60);
    ant->setSatiety(30);
    ant->setMaxCargo(50);
    ant->setCargo(50);

    ant->eatFromCargo();

    CHECK(ant->satiety() == 50);
    CHECK(int16_t(ant->satietyPercent() * 10) == 833);
    CHECK(ant->cargo() == 30);
    CHECK(int16_t(ant->cargoPercent() * 10) == 600);

    // 
    ant->eatFromCargo();

    CHECK(ant->satiety() == 60);
    CHECK(int16_t(ant->satietyPercent() * 10) == 1000);
    CHECK(ant->cargo() == 20);
    CHECK(int16_t(ant->cargoPercent() * 10) == 400);
}

TEST_CASE("basic", "[VM]")
{
    auto ant = runBCode(true, "basic.wasm");
    CHECK(ant->getValue(48) == 48);
    CHECK(ant->getValue(49) == 49);
    CHECK(ant->getValue(50) == 50);
    CHECK(ant->getValue(51) == 15);
    CHECK(ant->getValue(52) == 15);
}

TEST_CASE("arithmetic", "[VM]")
{
    auto ant = runBCode(true, "arithmetic.wasm");
    CHECK(ant->getValue(48) == 11);
    CHECK(ant->getValue(49) == 1);
}

TEST_CASE("min", "[VM]")
{
    auto ant = runBCode(true, "min.wasm");
    CHECK(ant->getValue(48) == 7);
    CHECK(ant->getValue(49) == 1);
}

TEST_CASE("max", "[VM]")
{
    auto ant = runBCode(true, "max.wasm");
    CHECK(ant->getValue(48) == 7);
    CHECK(ant->getValue(49) == 1);
}

TEST_CASE("bit", "[VM]")
{
    auto ant = runBCode(true, "bit.wasm");
    CHECK(ant->getValue(48) == 16);
    CHECK(ant->getValue(49) == 1);
    CHECK(ant->getValue(50) == 0x0160);
}

TEST_CASE("load", "[VM]")
{
    auto ant = runBCode(true, "load_bounded.wasm");
    CHECK(ant->getValue(48) == 3);
    CHECK(ant->getValue(49) == 1);
}

TEST_CASE("dist", "[VM]")
{
    auto ant = runBCode(true, "dist_bounded.wasm");
    CHECK(ant->getValue(48) == 6);
    CHECK(ant->getValue(49) == 1);
}

