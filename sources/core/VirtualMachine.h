#pragma once

#include <stdint.h>
#include <memory>
#include <vector>

#include "asm_defines.h"
#include "ant.h"

namespace WarAnts
{

class Ant;
class Map;
class Player;

class VirtualMachine
{
public:
    VirtualMachine(const std::shared_ptr<Map>& map, const std::shared_ptr<Ant>& ant);
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

    void prepare();
    int16_t* getDestination(Asm::Register::Type* type);
    int16_t getSource(Asm::Register::Type* type);

    void setRF(int16_t bit, bool value);

    bool arithmetic1(uint8_t cmd);
    bool arithmetic2(uint8_t cmd);
    bool min(uint8_t cmd);
    bool max(uint8_t cmd);
    bool logical(uint8_t cmd);
    bool jump(uint8_t cmd, uint16_t offset, uint8_t offsetType);
    void setDstAndFlags(int16_t* dst, int32_t value);

protected:
    const std::vector<int8_t>& m_bcode;
    std::vector<int16_t>& m_memory;

    std::shared_ptr<Ant> m_ant;
    std::shared_ptr<Map> m_map;

    VectorAnts m_allies;
    VectorAnts m_enemies;
    VectorPosition m_foods;
    std::vector<uint16_t> m_callstack;
    
    int16_t m_registers[Asm::Register::MASK];

    uint16_t m_pos = 0;
};

//using AntPtr = std::shared_ptr<Ant>;
//using VectorAnts = std::vector<std::shared_ptr<Ant>>;
//using ListAnts = std::list<std::shared_ptr<Ant>>;

};
