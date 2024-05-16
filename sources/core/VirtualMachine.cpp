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
    : m_bcode(ant->player()->info().bcode)
    , m_memory(ant->memory())
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
            m_ant->incValue(Memory::CountOfFood);
            m_foods.push_back(pos);
            continue;
        }

        auto cellAnt = cell->ant();
        if (cellAnt.get())
        {
            if (cellAnt->player() == m_ant->player())
            {
                m_ant->incValue(Memory::CountOfAllies);
                m_allies.push_back(cellAnt);
            }
            else
            {
                m_ant->incValue(Memory::CountOfEnemy);
                m_enemies.push_back(cellAnt);
            }
        }
    }

    m_ant->setValue(Memory::SatietyPercent, int16_t(m_ant->satietyPercent() * 10));
    m_ant->setValue(Memory::HealthPercent, int16_t(m_ant->healthPercent() * 10));
    m_ant->setValue(Memory::Cargo, m_ant->cargo());
}

int16_t* VirtualMachine::getDestination(Asm::Register::Type* type)
{
    int8_t reg = m_bcode[m_pos++];
    bool isAddress = reg & Asm::Register::ADDRESS;

    reg &= Asm::Register::MASK;

    if (type)
    {
        *type = Asm::Register::INVALIDE;
    }
    
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
        if (reg & Asm::Register::P0)
        {
            LOGE("Command %02x (%04x): Cannot using positional register as address",
                m_bcode[m_pos - 2], m_pos - 1);
            return nullptr;
        }

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

    if (type)
    {
        *type = (Asm::Register::Type)reg;
    }

    return &m_registers[reg];
}

int16_t VirtualMachine::getSource(Asm::Register::Type* type)
{
    auto ptr = getDestination(type);
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
            case Asm::BCode::DEC: result = arithmetic1(cmd); break;
            case Asm::BCode::DIV: result = arithmetic2(cmd); break;
            case Asm::BCode::INC: result = arithmetic1(cmd); break;
            case Asm::BCode::MOD: result = arithmetic2(cmd); break;
            case Asm::BCode::MUL: result = arithmetic2(cmd); break;
            case Asm::BCode::NEG: result = arithmetic1(cmd); break;
            case Asm::BCode::NOT: result = arithmetic1(cmd); break;
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
*/
            case Asm::BCode::EQ:   result = logical(cmd); break;
            case Asm::BCode::NEQ:  result = logical(cmd); break;
            case Asm::BCode::GT:   result = logical(cmd); break;
            case Asm::BCode::GE:   result = logical(cmd); break;
            case Asm::BCode::LT:   result = logical(cmd); break;
            case Asm::BCode::LE:   result = logical(cmd); break;
            case Asm::BCode::TEST: result = logical(cmd); break;

            case Asm::BCode::MOV: 
                dst = getDestination(nullptr);
                src = getSource(nullptr);
                if (dst)
                {
                    *dst = src;
                }
                break;
//                LEN,
//                DIST,
            case Asm::BCode::EXIT:
                if (m_callstack.empty())
                {
                    return true;
                }
                setPos(m_callstack.back());
                m_callstack.pop_back();
                break;
/*
                CMOV,
                CATT,
                CTKF,
                CGVF,
                CPS,
                CPW,
*/
            case Asm::BCode::JMP:  result = jump(cmd, value, valType); break;
            case Asm::BCode::JZ:   result = jump(cmd, value, valType); break;
            case Asm::BCode::JNZ:  result = jump(cmd, value, valType); break;
            case Asm::BCode::JO:   result = jump(cmd, value, valType); break;
            case Asm::BCode::JNO:  result = jump(cmd, value, valType); break;
            case Asm::BCode::JS:   result = jump(cmd, value, valType); break;
            case Asm::BCode::JNS:  result = jump(cmd, value, valType); break;
            case Asm::BCode::JCZ:  result = jump(cmd, value, valType); break;
            case Asm::BCode::JCNZ: result = jump(cmd, value, valType); break;
            case Asm::BCode::LOOP: result = jump(cmd, value, valType); break;
            case Asm::BCode::CALL: result = jump(cmd, value, valType); break;
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
    auto dst = getDestination(nullptr);

    CHECK_DST;

    int32_t tmp = *dst;

    switch (cmd)
    {
        case Asm::BCode::DEC: tmp -= 1; break;
        case Asm::BCode::INC: tmp += 1; break;
        case Asm::BCode::NEG: tmp = -tmp; break;
        case Asm::BCode::NOT: tmp = ~tmp; break;
        default:
            LOGE("Command %02x (%04x): Undefined the single arithmetic command", (int)cmd, cmdPos);
            SU_BREAKPOINT();
            return false;
    }

    setDstAndFlags(dst, tmp);
    return true;
}


bool VirtualMachine::arithmetic2(uint8_t cmd)
{
    auto cmdPos = pos();
    auto dst = getDestination(nullptr);
    auto src = getSource(nullptr);

    CHECK_DST;

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
            LOGE("Command %02x (%04x): Undefined the arithmetic command", (int)cmd, cmdPos);
            SU_BREAKPOINT();
            return false;
    }
    
    setDstAndFlags(dst, tmp);
    return true;
}

bool VirtualMachine::min(uint8_t cmd)
{
    auto cmdPos = pos();
    Asm::Register::Type regDst;
    Asm::Register::Type regSrc;
    auto dst = getDestination(&regDst);
    auto src = getDestination(&regSrc);

    CHECK_DST;

    if (regDst & Asm::Register::P0)
    {
        Position* posDest = (Position*)dst;
//        Position* posdest = (Position*)dst;
    }
    else
    {
        *dst = *dst < *src ? *dst : *src;
    }

    return true;
}

bool VirtualMachine::max(uint8_t cmd)
{
    return true;
}

bool VirtualMachine::logical(uint8_t cmd)
{
    auto cmdPos = pos();
    auto left = getSource(nullptr);
    auto right = getSource(nullptr);

    int16_t fakeDst = 0;
    int32_t result = 0;

    switch (cmd)
    {
        case Asm::BCode::EQ:   result = left == right; break;
        case Asm::BCode::NEQ:  result = left != right; break;
        case Asm::BCode::GT:   result = left >  right; break;
        case Asm::BCode::GE:   result = left >= right; break;
        case Asm::BCode::LT:   result = left <  right; break;
        case Asm::BCode::LE:   result = left <= right; break;
        case Asm::BCode::TEST: result = (left & right) == right; break;
        default:
            LOGE("Command %02x (%04x): Undefined the logical command", (int)cmd, cmdPos);
            SU_BREAKPOINT();
            return false;
    }

    setDstAndFlags(&fakeDst, result);
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
        case Asm::BCode::JMP:  doJump = true; break;
        case Asm::BCode::JZ:   doJump =  (m_registers[Asm::Register::RF] & Asm::Register::ZF); break;
        case Asm::BCode::JNZ:  doJump = !(m_registers[Asm::Register::RF] & Asm::Register::ZF); break;
        case Asm::BCode::JO:   doJump =  (m_registers[Asm::Register::RF] & Asm::Register::OF); break;
        case Asm::BCode::JNO:  doJump = !(m_registers[Asm::Register::RF] & Asm::Register::OF); break;
        case Asm::BCode::JS:   doJump =  (m_registers[Asm::Register::RF] & Asm::Register::SF); break;
        case Asm::BCode::JNS:  doJump = !(m_registers[Asm::Register::RF] & Asm::Register::SF); break;
        case Asm::BCode::JCZ:  doJump =   m_registers[Asm::Register::RC] == 0; break;
        case Asm::BCode::JCNZ: doJump =   m_registers[Asm::Register::RF] != 0; break;
        case Asm::BCode::LOOP: doJump =   m_registers[Asm::Register::RC] != 0; break;
        case Asm::BCode::CALL: doJump = true; break;
        default:
            LOGE("Command %02x (%04x): Undefined the jump command", (int)cmd, pos() - sizeCmd);
            SU_BREAKPOINT();
            return false;
    }

    if (doJump)
    {
        if (cmd == Asm::BCode::LOOP)
        {
            int32_t rc = m_registers[Asm::Register::RC] - 1;
            setDstAndFlags(&m_registers[Asm::Register::RC], rc);
        }

        setPos(newPos);
    }

    return true;
}

void VirtualMachine::setDstAndFlags(int16_t* dst, int32_t value)
{
    *dst = value & 0xffff;

    setRF(Asm::Register::ZF, *dst == 0);
    setRF(Asm::Register::OF, !!(value & 0xffff0000));
    setRF(Asm::Register::SF, !!(*dst & 0x8000));
}

};
