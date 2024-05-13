#include "VirtualMachine.h"

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
    VirtualMachineRunData(const std::vector<int8_t>& data);

    void prepareRunData(Ant* ant, Map* map);
    int16_t* getDestination();


public:
    VectorAnts allies;
    VectorAnts enemies;
    VectorPosition foods;
    std::vector<int16_t> memory;
    int8_t reg[Asm::Register::MASK];
};

void prepareRunData(VirtualMachineRunData& data, Ant* ant, Map* map)
{
    auto visibleCells = Math::visibleCells(ant->position(), ant->visibility());

    data.allies.clear();
    data.enemies.clear();
    data.foods.clear();
    data.memory.clear();

    data.memory.resize(Memory::UserData + ant->sizeOfMemory());

    for (auto& pos : visibleCells)
    {
        auto cell = map->cell(pos);

        if (cell->isEmpty())
        {
            continue;
        }

        if (cell->food())
        {
            ++data.memory[Memory::CountOfFood];
            data.foods.push_back(pos);
            continue;
        }

        auto cellAnt = cell->ant();
        if (cellAnt.get())
        {
            if (cellAnt->player() == ant->player())
            {
                ++data.memory[Memory::CountOfAllies];
                data.allies.push_back(cellAnt);
            }
            else
            {
                ++data.memory[Memory::CountOfEnemy];
                data.enemies.push_back(cellAnt);
            }
        }
    }

    data.memory[Memory::SatietyPercent] = int16_t(ant->satietyPercent() * 10);
    data.memory[Memory::HealthPercent] = int16_t(ant->healthPercent() * 10);
    data.memory[Memory::Cargo] = ant->cargo();

    for (size_t ii = 0; ii < ant->sizeOfMemory(); ++ii)
    {
        data.memory[UserData + ii] = ant->memory(ii);
    }
}

int16_t* getDestination(const std::vector<int8_t>& bcode, uint16_t& pos, int16_t* registers)
{
    int8_t reg = bcode[++pos];
    int16_t* out = nullptr;
    bool isAddress = reg & Asm::Register::ADDRESS;

    reg &= Asm::Register::MASK;
    
    if (reg > Asm::Register::MASK)
    {
        LOGE("Command %02x (%04x): Undefined register type %i", bcode[pos - 2], pos - 1, bcode[pos - 1]);
        return out;
    }

    out = &registers[Asm::Register::R0];

    if (isAddress)
    {
        out
    }

}

int16_t getSourceValue(const std::vector<int8_t>& bcode, uint16_t& pos, int16_t* reg)
{
    int8_t reg = bcode[++pos];
    int16_t val = 0;
    bool isAddress = reg & Asm::Register::ADDRESS;

    reg &= Asm::Register::MASK;
    switch (reg)
    {
        case Asm::Register::R0:
        case Asm::Register::R1:
        case Asm::Register::R2:
        case Asm::Register::P0X:
        case Asm::Register::P0Y:
        case Asm::Register::P1X:
        case Asm::Register::P1Y:
        case Asm::Register::P2X:
        case Asm::Register::P2Y:
        case Asm::Register::CHAR: val = bcode[++pos]; break;
        case Asm::Register::SHORT: val = bcode[++pos]; val |= bcode[++pos] << 8; break;
    }
    else if 

}


bool VirtualMachine::run(Ant* ant)
{
    VirtualMachineRunData data;
    auto plr = ant->player();
    auto bcode = plr->bcode();
    
    prepareRunData(data, ant, m_map.get());

    uint16_t pos = 0;

    if (ant->isQueen())
    {
        pos = bcode[Asm::FunctionOffset::Queen];
    }
    else if (ant->isSolder())
    {
        pos = bcode[Asm::FunctionOffset::Solder];
    }
    else if (ant->isWorker())
    {
        pos = bcode[Asm::FunctionOffset::Worker];
    }
    else
    {
        SU_BREAKPOINT();
        return false;
    }

    int8_t reg[16];
    int8_t cmd = 0;
    int8_t dst = 0;
    int8_t src = 0;
    while (true)
    {
        int8_t cmd = bcode[pos];

        if ((cmd & (int8_t)Asm::BCodeType::VALUE) == (int8_t)Asm::BCodeType::VALUE)
        {
            src = cmd & 0x03;
            cmd &= 0xfc;
        }

        switch ((Asm::BCodeCommand)cmd)
        {
//            case Asm::BCodeCommand::ADD:

/*
                AND,
                DEC,
                DIV,
                INC,
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

            case Asm::BCodeCommand::MOV:
                dst = bcode[++pos];

                src = bcode[++pos];
/*
                LEN,
                DIST,
                EXIT,

                CMOV,
                CATT,
                CTKF,
                CGVF,
                CPS,
                CPW,

                JMP = 0x40,
                JMPl = 0x41,
                JZ = 0x42,
                JZl = 0x43,
                JNZ = 0x44,
                JNZl = 0x45,
                JO = 0x46,
                JOl = 0x47,
                JNO = 0x48,
                JNOl = 0x49,
                JCZ = 0x4a,
                JCZl = 0x4b,
                JCNZ = 0x4c,
                JCNZl = 0x4d,
                LOOP = 0x4e,
                LOOPl = 0x4f,
                CALL = 0x50,
                CALLl = 0x51,

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
