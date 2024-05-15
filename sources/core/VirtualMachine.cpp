#include "VirtualMachine.h"

#include "log.h"
#include "defines.h"
#include "wacfile.h"

#include "Cell.h"
#include "Map.h"
#include "MapMath.h"
#include "memory.h"
#include "Player.h"

namespace WarAnts
{

VirtualMachine::VirtualMachine(const std::shared_ptr<Map>& map, const std::shared_ptr<Ant>& ant)
    : m_bcode(m_ant->player()->info().bcode)
    , m_memory(m_ant->memory())
{
    auto wac = m_ant->player()->info();

    m_ant = ant;
    m_map = map;

    if (ant->isQueen())
    {
        setPos(wac.funcQueen);
    }
    else if (ant->isSolder())
    {
        setPos(wac.funcSolder);
    }
    else if (ant->isWorker())
    {
        setPos(wac.funcWorker);
    }
    else
    {
        SU_BREAKPOINT();
        return;
    }

    prepare();
}

void VirtualMachine::prepare()
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
}

int16_t* VirtualMachine::getDestination()
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

        if (m_registers[reg] <= Memory::ReadOnly)
        {
            LOGE("Command %02x (%04x): address 0x04x is readonly",
                m_bcode[m_pos - 2], m_pos - 1, m_registers[reg]);
            return nullptr;
        }

        return &m_memory[m_registers[reg]];
    }

    return &m_registers[reg];
}

int16_t VirtualMachine::getSource()
{
    auto ptr = getDestination();
    return ptr ? *ptr : 0;
}

bool VirtualMachine::run()
{
    uint8_t cmd = 0;
    int16_t* dst = 0;
    int16_t src = 0;
    int16_t value = 0;
    uint8_t valType = 0;
    bool usingValue = false;
    bool result = true;
    
    m_callstack.clear();

    while (true)
    {
        usingValue = false;
        cmd = getNextChar();

        if ((cmd & Asm::BCode::TYPE_VALUE) == Asm::BCode::TYPE_VALUE)
        {
            valType = cmd & Asm::BCode::VALUE_MASK;
            cmd &= ~Asm::BCode::VALUE_MASK;

            if (valType == Asm::BCode::VALUE_CHAR)
            {
                usingValue = true;
                value = getNextChar();
            }
            else if (valType == Asm::BCode::VALUE_SHORT)
            {
                usingValue = true;
                value = getNextChar();
                value |= getNextChar() << 8;
            }
        }
        else if ((cmd & Asm::BCode::TYPE_JUMP) == Asm::BCode::TYPE_JUMP)
        {
            valType = cmd & Asm::BCode::JUMP_MASK;
            cmd &= ~Asm::BCode::JUMP_MASK;
            value = getNextChar();

            if (valType == Asm::BCode::JUMP_SHORT)
            {
                value |= getNextChar() << 8;
            }
        }

        switch (cmd)
        {
            case Asm::BCode::ADD: result = arithmetic2(cmd); break;
            case Asm::BCode::AND: result = arithmetic2(cmd); break;

            case Asm::BCode::DEC:
                dst = getDestination();
                if (dst)
                {
                    *dst -= 1;
                }
                break;

            case Asm::BCode::DIV: result = arithmetic2(cmd); break;

            case Asm::BCode::INC:
                dst = getDestination();
                if (dst)
                {
                    *dst += 1;
                }
                break;
            case Asm::BCode::MOD: result = arithmetic2(cmd); break;
            case Asm::BCode::MUL: result = arithmetic2(cmd); break;
//                NEG,
//                NOT,
            case Asm::BCode::OR:  result = arithmetic2(cmd); break;
            case Asm::BCode::SUB: result = arithmetic2(cmd); break;
            case Asm::BCode::XOR: result = arithmetic2(cmd); break;
/*                MIN,
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
                dst = getDestination();
                src = getSource();
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
                setPos(callstack.back());
                callstack.pop_back();
                break;
/*
                CMOV,
                CATT,
                CTKF,
                CGVF,
                CPS,
                CPW,
*/
//                JMP = 0x40,
            case Asm::BCode::JZ:
/*                JNZ = 0x44,
                JO = 0x46,
                JNO = 0x48,
                JCZ = 0x4a,
                JCNZ = 0x4c,
                LOOP = 0x4e,*/
            case Asm::BCode::CALL:
                callstack.push_back(pos());
                setPos(pos() + value - 2 - (valType == Asm::BCode::JUMP_SHORT ? 1 : 0));
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
        if (!result)
        {
            return false;
        }
    }

    return true;
}

void VirtualMachine::setRF(int16_t bit, bool value)
{
    if (value)
    {
        m_registers[Asm::Register::RF] |= bit;
    }
    else
    {
        m_registers[Asm::Register::RF] &= ~bit;
    }
}

#define CHECK_DST            if (!dst) { return false; }

bool VirtualMachine::arithmetic1(uint8_t cmd)
{
    auto cmdPos = pos();
    auto dst = getDestination();

    CHECK_DST;

    int32_t tmp = *dst;

    switch (cmd)
    {
    case Asm::BCode::DEC: tmp -= 1; break;
    case Asm::BCode::INC: tmp += 1; break;
    case Asm::BCode::NEG: tmp = -tmp; break;
    case Asm::BCode::NOT: tmp = ~tmp; break;
    default:
        LOGE("Command %02x (%04x): Undefined arithmetic operand", (int)cmd, cmdPos);
        SU_BREAKPOINT();
        return false;
    }

    *dst = tmp & 0xffff;

    setRF(Asm::Register::ZF, *dst == 0);
    setRF(Asm::Register::OF, !!(tmp & 0xffff0000));
    return true;
}


bool VirtualMachine::arithmetic2(uint8_t cmd)
{
    auto cmdPos = pos();
    auto dst = getDestination();
    auto src = getSource();

    CHECK_DST;

    uint16_t oldDst = *dst;
    int32_t tmp = *dst;

    switch (cmd)
    {
        case Asm::BCode::ADD: tmp += src; break;
        case Asm::BCode::AND: tmp &= src; break;
        case Asm::BCode::DIV: tmp /= src; break;
        case Asm::BCode::MOD: tmp %= src; break;
        case Asm::BCode::MUL: tmp *= src; break;
        case Asm::BCode::OR:  tmp |= src; break;
        case Asm::BCode::SUB: tmp -= src; break;
        case Asm::BCode::XOR: tmp ^= src; break;
        default:
            LOGE("Command %02x (%04x): Undefined arithmetic operand", (int)cmd, cmdPos);
            SU_BREAKPOINT();
            return false;
    }
    
    *dst = tmp & 0xffff;
    
    setRF(Asm::Register::ZF, *dst == 0);
    setRF(Asm::Register::OF, !!(tmp & 0xffff0000));
    setRF(Asm::Register::SF, (oldDst & 0x8000) != (*dst & 0x8000);
    return true;
}

bool VirtualMachine::jump(uint8_t cmd, uint16_t offset, uint8_t offsetType)
{
    if (cmd == Asm::BCode::CALL)
    {
        m_callstack.push_back(pos());
    }

    uint16_t sizeCmd = 2 + (offsetType == Asm::BCode::JUMP_SHORT ? 1 : 0);
    uint16_t newPos = pos() + offset - sizeCmd;
    bool doJump = false;

    switch (cmd)
    {
        case Asm::BCode::JMP: doJump = true;
    }
    setPos();
}


};
