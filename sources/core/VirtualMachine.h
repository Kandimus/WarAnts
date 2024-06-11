#pragma once

#include <stdint.h>
#include <memory>
#include <vector>

#include "asm_defines.h"
#include "ant.h"

namespace WarAnts
{

class Ant;
class Config;
class Map;
class Player;

class VirtualMachine
{
public:
    struct Argument
    {
        int16_t* ptr;
        uint8_t  reg;
        bool     pos;
        bool     adr;
        uint16_t offset;
    };

public:
    VirtualMachine(uint32_t iteration, const std::shared_ptr<Map>& map, const std::shared_ptr<Ant>& ant);
    VirtualMachine(const VirtualMachine&) = delete;
    VirtualMachine(VirtualMachine&&) = delete;
    virtual ~VirtualMachine() = default;

    VirtualMachine& operator=(const VirtualMachine& ant) = delete;

public:
    bool run();

protected:
    uint16_t pos() const { return m_pos; }
    void setPos(uint16_t pos) { m_pos = pos; };
    int8_t getNextChar() { ++m_pos; return m_bcode[m_pos - 1]; }

    void prepare(uint32_t iteration);
    Argument getRegisterArgument();

    void setRF(int16_t bit, bool value);

    void setCommand(Command::Type cmd, const Position& pos);

    bool arithmetic1(uint8_t cmd);
    bool arithmetic2(uint8_t cmd);
    bool minmax(uint8_t cmd);
    bool bit(uint8_t cmd);
    bool logical(uint8_t cmd);
    bool jump(uint8_t cmd, uint16_t offset, uint8_t offsetType);
    bool value1(uint8_t cmd, uint16_t offset, uint8_t offsetType);
    bool length(int8_t cmd);
    bool ret(bool& exit);
    bool commandPositionArg(int8_t cmd);
    bool commandNoArgs(int8_t cmd);
    bool mapSize();
    void setDstAndFlags(int16_t* dst, int32_t value);
    bool checkLVal(const Argument& arg);
    bool bsf(int16_t* bitno, int16_t src);
    bool bsr(int16_t* bitno, int16_t src);
    bool bitTest(uint8_t cmd, int16_t* dst, int16_t src);
    bool shiftLeft(bool restore, int16_t* dst, int16_t src);
    bool shiftRight(bool restore, int16_t* dst, int16_t src);
    bool loadReceivedData(int16_t value);
    bool loadFood(int16_t value);
    bool loadAlly(int16_t value);
    bool loadEnemy(int16_t value);
    bool printDebug(int16_t value);

protected:
    struct FoodInfo
    {
        int16_t count;
        Position pos;
    };

    const std::vector<int8_t>& m_bcode;
    std::vector<int16_t>& m_memory;

    std::shared_ptr<Ant> m_ant;
    std::shared_ptr<Map> m_map;
    std::shared_ptr<Config> m_conf;

    std::vector<Ant*> m_allies;
    std::vector<Ant*> m_enemies;
    std::vector<FoodInfo> m_foods;
    std::vector<uint16_t> m_callstack;
    
    int16_t m_registers[Asm::Register::COUNT];

    uint16_t m_pos = 0;
};

//using AntPtr = std::shared_ptr<Ant>;
//using VectorAnts = std::vector<std::shared_ptr<Ant>>;
//using ListAnts = std::list<std::shared_ptr<Ant>>;

};
