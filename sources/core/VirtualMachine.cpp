#include "VirtualMachine.h"

#include "log.h"

#include "asm_defines.h"
#include "defines.h"

#include "Ant.h"
#include "Cell.h"
#include "Map.h"
#include "MapMath.h"
#include "Player.h"

namespace WarAnts
{

enum Memory
{
    SatietyPercent = 0x02,
    HealthPercent = 0x03,
    Cargo = 0x04,
    CountOfAllies = 0x05,
    CountOfEnemy = 0x06,
    CountOfFood = 0x07,

    UserData = 0x30,
};

class VirtualMachineRunData
{
public:
    VirtualMachineRunData(const std::vector<int8_t>& data, const std::shared_ptr<Ant>& ant, const std::shared_ptr<Map>& map)
        : m_bcode(data)
    {
        m_ant = ant;
        m_map = map;

        m_memory.resize(Memory::UserData + m_ant->sizeOfMemory()); //TODO возможно нужно перенести это в класс Ant

        prepare();
    }

    uint16_t pos() const { return m_pos; }
    void setPos(uint16_t pos) { m_pos = pos; };
    int8_t getNextChar() { ++m_pos; return m_bcode[m_pos - 1]; }

    void prepare();
    int16_t* getDestination();
    int16_t getSource();

public:
    const std::vector<int8_t>& m_bcode;

    std::shared_ptr<Ant> m_ant;
    std::shared_ptr<Map> m_map;

    VectorAnts m_allies;
    VectorAnts m_enemies;
    VectorPosition m_foods;
    std::vector<int16_t> m_memory;
    int16_t m_registers[Asm::Register::MASK];

    uint16_t m_pos = 0;
};

void VirtualMachineRunData::prepare()
{
    auto visibleCells = Math::visibleCells(m_ant->position(), m_ant->visibility());

    for (auto& pos : visibleCells)
    {
        auto cell = m_map->cell(pos);

        if (!cell || cell->isEmpty())
        {
            continue;
        }

        if (cell->food())
        {
            ++m_memory[Memory::CountOfFood];
            m_foods.push_back(pos);
            continue;
        }

        auto cellAnt = cell->ant();
        if (cellAnt.get())
        {
            if (cellAnt->player() == m_ant->player())
            {
                ++m_memory[Memory::CountOfAllies];
                m_allies.push_back(cellAnt);
            }
            else
            {
                ++m_memory[Memory::CountOfEnemy];
                m_enemies.push_back(cellAnt);
            }
        }
    }

    m_memory[Memory::SatietyPercent] = int16_t(m_ant->satietyPercent() * 10);
    m_memory[Memory::HealthPercent] = int16_t(m_ant->healthPercent() * 10);
    m_memory[Memory::Cargo] = m_ant->cargo();

    for (size_t ii = 0; ii < m_ant->sizeOfMemory(); ++ii)
    {
        m_memory[UserData + ii] = m_ant->memory(ii);
    }
}

int16_t* VirtualMachineRunData::getDestination()
{
    int8_t reg = m_bcode[m_pos++];
    bool isAddress = reg & Asm::Register::ADDRESS;

    reg &= Asm::Register::MASK;
    
    if (reg > Asm::Register::MASK)
    {
        LOGE("Command %02x (%04x): Undefined register type %i",
            m_bcode[m_pos - 2], m_pos - 1, m_bcode[m_pos - 1]);
        return nullptr;
    }

    if (reg == Asm::Register::CHAR)
    {
        m_registers[Asm::Register::CHAR] = m_bcode[m_pos++];
    }
    else if (reg == Asm::Register::SHORT)
    {
        m_registers[Asm::Register::SHORT] = m_bcode[m_pos++];
        m_registers[Asm::Register::SHORT] |= (m_bcode[m_pos++] << 8);
    }

    if (isAddress)
    {
        if (m_registers[reg] >= m_memory.size())
        {
            LOGE("Command %02x (%04x): invalide address 0x04x",
                m_bcode[m_pos - 2], m_pos - 1, m_registers[reg]);
            return nullptr;
        }

        if (m_registers[reg] < Memory::UserData)
        {
            LOGE("Command %02x (%04x): address 0x04x is readonly",
                m_bcode[m_pos - 2], m_pos - 1, m_registers[reg]);
            return nullptr;
        }

        return &m_memory[m_registers[reg]];
    }

    return &m_registers[reg];
}

int16_t VirtualMachineRunData::getSource()
{
    auto ptr = getDestination();
    return ptr ? *ptr : 0;
}

bool VirtualMachine::run(const std::shared_ptr<Ant>& ant)
{
    auto plr = ant->player();
    auto wac = plr->info();

    VirtualMachineRunData data(wac.bcode, ant, m_map);

    if (ant->isQueen())
    {
        data.setPos(wac.funcQueen);
    }
    else if (ant->isSolder())
    {
        data.setPos(wac.funcSolder);
    }
    else if (ant->isWorker())
    {
        data.setPos(wac.funcWorker);
    }
    else
    {
        SU_BREAKPOINT();
        return false;
    }

    int8_t cmd = 0;
    int16_t* dst = 0;
    int16_t src = 0;
    int16_t value = 0;
    uint8_t valType = 0;
    bool usingValue = false;
    std::vector<uint16_t> callstack;

    while (true)
    {
        usingValue = false;
        cmd = data.getNextChar();

        if ((cmd & Asm::BCode::TYPE_VALUE) == Asm::BCode::TYPE_VALUE)
        {
            valType = cmd & Asm::BCode::VALUE_MASK;
            cmd &= ~Asm::BCode::VALUE_MASK;

            if (valType == Asm::BCode::VALUE_CHAR)
            {
                usingValue = true;
                value = data.getNextChar();
            }
            else if (valType == Asm::BCode::VALUE_SHORT)
            {
                usingValue = true;
                value = data.getNextChar();
                value |= data.getNextChar() << 8;
            }
        }
        else if ((cmd & Asm::BCode::TYPE_JUMP) == Asm::BCode::TYPE_JUMP)
        {
            valType = cmd & Asm::BCode::JUMP_MASK;
            cmd &= ~Asm::BCode::JUMP_MASK;
            value = data.getNextChar();

            if (valType == Asm::BCode::JUMP_SHORT)
            {
                value |= data.getNextChar() << 8;
            }
        }

        switch (cmd)
        {
            case Asm::BCode::ADD:
                dst = data.getDestination();
                src = data.getSource();
                if (dst)
                {
                    *dst = *dst + src;
                }
                break;

            case Asm::BCode::AND:
                dst = data.getDestination();
                src = data.getSource();
                if (dst)
                {
                    *dst = *dst & src;
                }
                break;

            case Asm::BCode::DEC:
                dst = data.getDestination();
                if (dst)
                {
                    *dst -= 1;
                }
                break;

            case Asm::BCode::DIV:
                dst = data.getDestination();
                src = data.getSource();
                if (dst)
                {
                    *dst = *dst / src;
                }
                break;

            case Asm::BCode::INC:
                dst = data.getDestination();
                if (dst)
                {
                    *dst += 1;
                }
                break;
/*
                MOD,
                MUL,
                NEG,
                NOT,
                OR,
                SUB,
                XOR,
                MIN,
                MAX,

                BSF,
                BSR,
                BT,
                BTR,
                BTS,
                BTC,
                SHL,
                SHR,
                ROL,
                ROR,

                EQ,
                NEQ,
                GT,
                GE,
                LT,
                LE,
                TEST,
*/

            case Asm::BCode::MOV: 
                dst = data.getDestination();
                src = data.getSource();
                if (dst)
                {
                    *dst = src;
                }
                break;
//                LEN,
//                DIST,
            case Asm::BCode::EXIT:
                if (callstack.empty())
                {
                    return true;
                }
                data.setPos(callstack.back());
                callstack.pop_back();
                break;
/*
                CMOV,
                CATT,
                CTKF,
                CGVF,
                CPS,
                CPW,

                JMP = 0x40,
                JZ = 0x42,
                JNZ = 0x44,
                JO = 0x46,
                JNO = 0x48,
                JCZ = 0x4a,
                JCNZ = 0x4c,
                LOOP = 0x4e,*/
            case Asm::BCode::CALL:
                callstack.push_back(data.pos());
                data.setPos(data.pos() + value - 2 - (valType == Asm::BCode::JUMP_SHORT ? 1 : 0));
                break;
/*
                LDTR = 0x60,
                LDFD = 0x64,
                LDEN = 0x68,
                LDFR = 0x6c,
                CIDL = 0x70,
                CEAT = 0x74,
*/
        }
    }

}


};
