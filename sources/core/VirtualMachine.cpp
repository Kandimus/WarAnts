#include "VirtualMachine.h"

#include <fstream>

#include "stringex.h"

#include "log.h"
#include "defines.h"
#include "wacfile.h"

#include "Cell.h"
#include "Config.h"
#include "Map.h"
#include "MapMath.h"
#include "memory.h"
#include "Player.h"

#pragma warning(disable:6385)

namespace WarAnts
{

VirtualMachine::VirtualMachine(uint32_t iteration, const std::shared_ptr<Map>& map, const std::shared_ptr<Ant>& ant)
    : m_bcode(ant->player()->info().bcode)
    , m_memory(ant->memory())
{
    m_ant = ant;
    m_map = map;
    m_conf = map->config();

    auto wac = m_ant->player()->info();

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

    prepare(iteration);
}

void VirtualMachine::prepare(uint32_t iteration)
{
    m_map->processingRadius(m_ant->position(), m_ant->visibility(), [this](const Cell& cell)
    {
        if (cell.food())
        {
            m_foods.push_back(FoodInfo());
            m_foods.back().count = cell.food();
            m_foods.back().pos = cell.position();
            return;
        }

        auto ant = cell.ant();
        if (!ant)
        {
            return;
        }

        if (m_ant.get() == ant)
        {
            return;
        }

        if (ant->status() != Ant::Status::Life)
        {
            return;
        }

        if (ant->player() == m_ant->player())
        {
            m_allies.push_back(ant);
        }
        else
        {
            m_enemies.push_back(ant);
        }
    });

    su::UniInt32 iter;
    iter.u32 = iteration;

    // Clear system data
    memset(m_memory.data(), 0, sizeof(int16_t) * Memory::UserData);

    m_memory[Memory::Iteration] = iter.i16[0];
    m_memory[Memory::Iteration + 1] = iter.i16[1];
    m_memory[Memory::SatietyPercent] = int16_t(m_ant->satietyPercent() * 10);
    m_memory[Memory::SatietyPercent] = int16_t(m_ant->satietyPercent() * 10);
    m_memory[Memory::HealthPercent] = int16_t(m_ant->healthPercent() * 10);
    m_memory[Memory::Cargo] = int16_t(m_ant->cargoPercent() * 10);
    m_memory[Memory::CountOfAllies] = (int16_t)m_allies.size();
    m_memory[Memory::CountOfEnemies] = (int16_t)m_enemies.size();
    m_memory[Memory::CountOfFoods] = (int16_t)m_foods.size();
    m_memory[Memory::CountOfReceivedData] = (int16_t)m_ant->receivedData().size();
    //CountOfWorkers = 0x09,
    //CountOfSolders = 0x0a,
    m_memory[Memory::InterruptReason] = m_ant->interruptReason();
    m_memory[Memory::CommandId] = (int16_t)m_ant->command().m_type;
    m_memory[Memory::CommandX] = m_ant->command().m_pos.x();
    m_memory[Memory::CommandY] = m_ant->command().m_pos.y();
    m_memory[Memory::CommandValue] = m_ant->command().m_value;

    m_memory[Memory::InterruptFlags] = m_ant->interruptFlags();
}

VirtualMachine::Argument VirtualMachine::getRegisterArgument()
{
    Argument out;
    int8_t reg = m_bcode[m_pos++];

    out.reg = reg & Asm::Register::COUNT;
    out.pos = reg & Asm::Register::POSITION;
    out.adr = reg & Asm::Register::ADDRESS;
    out.ptr = &m_registers[out.reg];
    out.offset = m_pos - 1;
    
    if (out.reg == Asm::Register::CHAR)
    {
        m_registers[Asm::Register::CHAR] = m_bcode[m_pos++];
    }
    else if (out.reg == Asm::Register::SHORT)
    {
        su::UniInt16 val = { 0 };
        val.i8[0] = m_bcode[m_pos++];
        val.i8[1] = m_bcode[m_pos++];
        m_registers[Asm::Register::SHORT] = val.i16;
    }

    if (out.adr)
    {
        if (m_registers[out.reg] < 0)
        {
            LOGE("Command %02x (%04x): invalide address 0x04x", m_bcode[m_pos - 2],
                m_pos - 1, m_registers[out.reg]);
            out.ptr = nullptr;
            return out;
        }

        if ((size_t)m_registers[out.reg] >= m_memory.size())
        {
            LOGE("Command %02x (%04x): invalide address 0x04x", m_bcode[m_pos - 2],
                m_pos - 1, m_registers[out.reg]);
            out.ptr = nullptr;
            return out;
        }
        out.ptr = &m_memory[m_registers[out.reg]];
    }

    return out;
}

bool VirtualMachine::run()
{
    uint8_t cmd = 0;
    int16_t* dst = 0;
    int16_t src = 0;
    uint8_t valType = 0;
    su::UniInt16 value = { 0 };
    bool result = true;
    bool exit = false;
    
    m_callstack.clear();

    while (!exit)
    {
        cmd = getNextChar();

        if ((cmd & Asm::BCode::TYPE_VALUE) == Asm::BCode::TYPE_VALUE)
        {
            valType = cmd & Asm::BCode::VALUE_MASK;
            cmd &= ~Asm::BCode::VALUE_MASK;

            if (valType == Asm::BCode::VALUE_SHORT)
            {
                value.i8[0] = getNextChar();
                value.i8[1] = getNextChar();
            }
            else if (valType == Asm::BCode::VALUE_CHAR)
            {
                value.i16 = getNextChar();
            }
        }
        else if ((cmd & Asm::BCode::TYPE_JUMP) == Asm::BCode::TYPE_JUMP)
        {
            valType = cmd & Asm::BCode::JUMP_MASK;
            cmd &= ~Asm::BCode::JUMP_MASK;
            
            if (valType == Asm::BCode::JUMP_SHORT)
            {
                value.i8[0] = getNextChar();
                value.i8[1] = getNextChar();
            }
            else
            {
                value.i16 = getNextChar();
            }
        }

        switch (cmd)
        {
            case Asm::BCode::ADD:  result = arithmetic2(cmd); break;
            case Asm::BCode::AND:  result = arithmetic2(cmd); break;
            case Asm::BCode::DEC:  result = arithmetic1(cmd); break;
            case Asm::BCode::DIV:  result = arithmetic2(cmd); break;
            case Asm::BCode::INC:  result = arithmetic1(cmd); break;
            case Asm::BCode::MOD:  result = arithmetic2(cmd); break;
            case Asm::BCode::MUL:  result = arithmetic2(cmd); break;
            case Asm::BCode::NEG:  result = arithmetic1(cmd); break;
            case Asm::BCode::NOT:  result = arithmetic1(cmd); break;
            case Asm::BCode::OR:   result = arithmetic2(cmd); break;
            case Asm::BCode::SUB:  result = arithmetic2(cmd); break;
            case Asm::BCode::XOR:  result = arithmetic2(cmd); break;
            case Asm::BCode::MIN:  result = minmax(cmd); break;
            case Asm::BCode::MAX:  result = minmax(cmd); break;

            case Asm::BCode::BSF:  result = bit(cmd); break;
            case Asm::BCode::BSR:  result = bit(cmd); break;
            case Asm::BCode::BT:   result = bit(cmd); break;
            case Asm::BCode::BTR:  result = bit(cmd); break;
            case Asm::BCode::BTS:  result = bit(cmd); break;
            case Asm::BCode::BTC:  result = bit(cmd); break;
            case Asm::BCode::SHL:  result = bit(cmd); break;
            case Asm::BCode::SHR:  result = bit(cmd); break;
            case Asm::BCode::ROL:  result = bit(cmd); break;
            case Asm::BCode::ROR:  result = bit(cmd); break;

            case Asm::BCode::EQ:   result = logical(cmd); break;
            case Asm::BCode::NEQ:  result = logical(cmd); break;
            case Asm::BCode::GT:   result = logical(cmd); break;
            case Asm::BCode::GE:   result = logical(cmd); break;
            case Asm::BCode::LT:   result = logical(cmd); break;
            case Asm::BCode::LE:   result = logical(cmd); break;
            case Asm::BCode::TEST: result = logical(cmd); break;

            case Asm::BCode::MOV:  result = arithmetic2(cmd); break;
            case Asm::BCode::LEN:  result = length(cmd); break;
            case Asm::BCode::DIST: result = length(cmd); break;
            case Asm::BCode::RET:  result = ret(exit); break;
            case Asm::BCode::MPSZ: result = mapSize(); break;

            case Asm::BCode::CMOV: result = commandPositionArg(cmd); break;
            case Asm::BCode::CATT: result = commandPositionArg(cmd); break;
            case Asm::BCode::CFD:  result = commandPositionArg(cmd); break;
            case Asm::BCode::CTKF: result = commandPositionArg(cmd); break;
            case Asm::BCode::CEAT: result = commandNoArgs(cmd); break;
            case Asm::BCode::CCTR: result = commandPositionArg(cmd); break;
            case Asm::BCode::CCSL: result = commandNoArgs(cmd); break;
            case Asm::BCode::CCWR: result = commandNoArgs(cmd); break;

            case Asm::BCode::JMP:  result = jump(cmd, value.i16, valType); break;
            case Asm::BCode::JZ:   result = jump(cmd, value.i16, valType); break;
            case Asm::BCode::JNZ:  result = jump(cmd, value.i16, valType); break;
            case Asm::BCode::JO:   result = jump(cmd, value.i16, valType); break;
            case Asm::BCode::JNO:  result = jump(cmd, value.i16, valType); break;
            case Asm::BCode::JS:   result = jump(cmd, value.i16, valType); break;
            case Asm::BCode::JNS:  result = jump(cmd, value.i16, valType); break;
            case Asm::BCode::JCZ:  result = jump(cmd, value.i16, valType); break;
            case Asm::BCode::JCNZ: result = jump(cmd, value.i16, valType); break;
            case Asm::BCode::LOOP: result = jump(cmd, value.i16, valType); break;
            case Asm::BCode::CALL: result = jump(cmd, value.i16, valType); break;

            case Asm::BCode::LDRC: result = value1(cmd, value.i16, valType); break;
            case Asm::BCode::LDFD: result = value1(cmd, value.i16, valType); break;
            case Asm::BCode::LDEN: result = value1(cmd, value.i16, valType); break;
            case Asm::BCode::LDAL: result = value1(cmd, value.i16, valType); break;
            case Asm::BCode::CIDL: result = value1(cmd, value.i16, valType); break;
            case Asm::BCode::DBG:  result = value1(cmd, value.i16, valType); break;
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

void VirtualMachine::setCommand(Command::Type cmd, const Position& pos, Command::Target target)
{
    m_ant->command().setCompleted(false);
    m_ant->command().m_type = cmd;
    m_ant->command().setPosition(pos);
    m_ant->command().m_value = 2 * Math::distanceTo(m_ant->position(), pos);
    m_ant->command().setTarget(target);
    m_ant->command().setAnt(target == Command::Ant ? m_map->cell(pos)->ant() : nullptr);
}

#define CHECK_PTR(x)            if (!(x).ptr) { return false; }
#define CHECK_LVAL(x)           if (!(x).ptr || !checkLVal(x)) { return false; }

bool VirtualMachine::arithmetic1(uint8_t cmd)
{
    auto cmdPos = pos() - 1;
    auto dst = getRegisterArgument();

    CHECK_LVAL(dst);

    if (dst.pos)
    {
        Position pos(dst.ptr[0], dst.ptr[1]);
        switch (cmd)
        {
            case Asm::BCode::DEC: pos.dec(); break;
            case Asm::BCode::INC: pos.inc(); break;
            case Asm::BCode::NEG: pos.neg(); break;
            default:
                LOGE("Command %02x (%04x): Undefined the position arithmetic command", (int)cmd, cmdPos);
                SU_BREAKPOINT();
                return false;
        }
        pos.store(dst.ptr);
        return true;
    }

    int32_t tmp = *dst.ptr;
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

    setDstAndFlags(dst.ptr, tmp);
    return true;
}


bool VirtualMachine::arithmetic2(uint8_t cmd)
{
    auto cmdPos = pos() - 1;
    auto dst = getRegisterArgument();
    auto src = getRegisterArgument();

    CHECK_LVAL(dst);

    if (dst.pos)
    {
        Position dstPos(dst.ptr[0], dst.ptr[1]);
        Position srcPos = src.pos ? Position(src.ptr[0], src.ptr[1]) : Position(*src.ptr);

        switch (cmd)
        {
            case Asm::BCode::ADD: dstPos += srcPos; break;
            case Asm::BCode::DIV: dstPos /= srcPos; break;
            case Asm::BCode::MUL: dstPos *= srcPos; break;
            case Asm::BCode::SUB: dstPos -= srcPos; break;
            case Asm::BCode::MOV: dstPos  = srcPos; break;
            default:
                LOGE("Command %02x (%04x): Undefined the position arithmetic command", (int)cmd, cmdPos);
                SU_BREAKPOINT();
                return false;
        }

        dstPos.store(dst.ptr);
        return true;
    }

    int32_t tmp = *dst.ptr;
    switch (cmd)
    {
        case Asm::BCode::ADD: tmp += *src.ptr; break;
        case Asm::BCode::AND: tmp &= *src.ptr; break;
        case Asm::BCode::DIV: tmp /= *src.ptr; break;
        case Asm::BCode::MOD: tmp %= *src.ptr; break;
        case Asm::BCode::MUL: tmp *= *src.ptr; break;
        case Asm::BCode::OR:  tmp |= *src.ptr; break;
        case Asm::BCode::SUB: tmp -= *src.ptr; break;
        case Asm::BCode::XOR: tmp ^= *src.ptr; break;
        case Asm::BCode::MOV: tmp  = *src.ptr; break;
        default:
            LOGE("Command %02x (%04x): Undefined the arithmetic command", (int)cmd, cmdPos);
            SU_BREAKPOINT();
            return false;
    }
    
    setDstAndFlags(dst.ptr, tmp);
    return true;
}

bool VirtualMachine::minmax(uint8_t cmd)
{
    auto cmdPos = pos() - 1;
    auto dst = getRegisterArgument();
    auto src = getRegisterArgument();

    CHECK_LVAL(dst);

    if (dst.pos)
    {
        Position dstPos(dst.ptr[0], dst.ptr[1]);
        Position srcPos = src.pos ? Position(src.ptr[0], src.ptr[1]) : Position(*src.ptr);

        switch (cmd)
        {
            case Asm::BCode::MIN: dstPos = dstPos.min(srcPos); break;
            case Asm::BCode::MAX: dstPos = dstPos.max(srcPos); break;
            default:
                LOGE("Command %02x (%04x): Undefined the position min/max command", (int)cmd, cmdPos);
                SU_BREAKPOINT();
                return false;
        }
        dstPos.store(dst.ptr);
        return true;
    }

    int32_t tmp = *dst.ptr;
    switch (cmd)
    {
        case Asm::BCode::MIN: tmp = tmp < *src.ptr ? tmp : *src.ptr; break;
        case Asm::BCode::MAX: tmp = tmp > *src.ptr ? tmp : *src.ptr; break;
        default:
            LOGE("Command %02x (%04x): Undefined the min/max command", (int)cmd, cmdPos);
            SU_BREAKPOINT();
            return false;
    }

    setDstAndFlags(dst.ptr, tmp);
    return true;
}

bool VirtualMachine::bit(uint8_t cmd)
{
    auto cmdPos = pos() - 1;

    auto dst = getRegisterArgument();
    auto src = getRegisterArgument();

    CHECK_LVAL(dst);

    if (dst.pos || src.pos)
    {
        LOGE("Command %02x (%04x): Wrong arguments of the bit command", (int)cmd, cmdPos);
        return false;
    }

    switch (cmd)
    {
        case Asm::BCode::BSF: setRF(Asm::Register::ZF, bsf(dst.ptr, *src.ptr)); break;
        case Asm::BCode::BSR: setRF(Asm::Register::ZF, bsr(dst.ptr, *src.ptr)); break;
        case Asm::BCode::BT:  setRF(Asm::Register::ZF, bitTest(cmd, dst.ptr, *src.ptr)); break;
        case Asm::BCode::BTR: setRF(Asm::Register::ZF, bitTest(cmd, dst.ptr, *src.ptr)); break;
        case Asm::BCode::BTS: setRF(Asm::Register::ZF, bitTest(cmd, dst.ptr, *src.ptr)); break;
        case Asm::BCode::BTC: setRF(Asm::Register::ZF, bitTest(cmd, dst.ptr, *src.ptr)); break;
        case Asm::BCode::SHL: setRF(Asm::Register::ZF, shiftLeft(false, dst.ptr, *src.ptr)); break;
        case Asm::BCode::SHR: setRF(Asm::Register::ZF, shiftRight(false, dst.ptr, *src.ptr)); break;
        case Asm::BCode::ROL: setRF(Asm::Register::ZF, shiftLeft(true, dst.ptr, *src.ptr)); break;
        case Asm::BCode::ROR: setRF(Asm::Register::ZF, shiftRight(true, dst.ptr, *src.ptr)); break;
        default:
            LOGE("Command %02x (%04x): Undefined the bit command", (int)cmd, cmdPos);
            SU_BREAKPOINT();
            return false;
    }

    return true;
}

bool VirtualMachine::logical(uint8_t cmd)
{
    auto cmdPos = pos() - 1;
    auto left = getRegisterArgument();
    auto right = getRegisterArgument();

    if (left.pos != right.pos)
    {
        LOGE("Command %02x (%04x): Wrong arguments of the logical command", (int)cmd, cmdPos);
        return false;
    }

    int32_t result = 0;
        
    if (left.pos)
    {
        Position leftPos(left.ptr[0], left.ptr[1]);
        Position rightPos(right.ptr[0], right.ptr[1]);
        switch (cmd)
        {
            case Asm::BCode::EQ:  result = (leftPos == rightPos); break;
            case Asm::BCode::NEQ: result = (leftPos != rightPos); break;
            default:
                LOGE("Command %02x (%04x): Undefined the position logical command", (int)cmd, cmdPos);
                SU_BREAKPOINT();
                return false;
        }
    }
    else
    {
        switch (cmd)
        {
            case Asm::BCode::EQ:   result = *left.ptr == *right.ptr; break;
            case Asm::BCode::NEQ:  result = *left.ptr != *right.ptr; break;
            case Asm::BCode::GT:   result = *left.ptr >  *right.ptr; break;
            case Asm::BCode::GE:   result = *left.ptr >= *right.ptr; break;
            case Asm::BCode::LT:   result = *left.ptr <  *right.ptr; break;
            case Asm::BCode::LE:   result = *left.ptr <= *right.ptr; break;
            case Asm::BCode::TEST: result = (*left.ptr & *right.ptr) == *right.ptr; break;
            default:
                LOGE("Command %02x (%04x): Undefined the logical command", (int)cmd, cmdPos);
                SU_BREAKPOINT();
                return false;
        }
    }

    int16_t fakeDst = 0;
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

bool VirtualMachine::value1(uint8_t cmd, uint16_t value, uint8_t valueType)
{
    auto cmdPos = pos() - 1 - (valueType == Asm::BCode::VALUE_CHAR || valueType == Asm::BCode::VALUE_SHORT) ? (valueType == Asm::BCode::VALUE_SHORT ? 2 : 1) : 0;

    if (valueType != Asm::BCode::VALUE_CHAR && valueType != Asm::BCode::VALUE_SHORT)
    {
        auto arg = getRegisterArgument();
        value = *arg.ptr;
    }

    bool result = true;
    switch (cmd)
    {
        case Asm::BCode::LDRC: result = loadReceivedData(value);
        case Asm::BCode::LDFD: result = loadFood(value); break;
        case Asm::BCode::LDEN: result = loadEnemy(value); break;
        case Asm::BCode::LDAL: result = loadAlly(value); break;
        case Asm::BCode::CIDL: result = true; m_ant->setCommand(Command::Type::Idle, value, Target::None); break;
        case Asm::BCode::DBG:  result = printDebug(value); break;
        default:
            LOGE("Command %02x (%04x): Undefined the logical command", (int)cmd, cmdPos);
            SU_BREAKPOINT();
            return false;
    }
    return true;
}

bool VirtualMachine::length(int8_t cmd)
{
    auto argTo = getRegisterArgument();
    
    if (!argTo.pos)
    {
        LOGE("Offset %04x: is not a position (reg 0x%02x)", argTo.offset, argTo.reg);
        return false;
    }
    Position posTo(argTo.ptr[0], argTo.ptr[1]);

    Position posFrom = m_ant->position();
    if (cmd == Asm::BCode::LEN)
    {
        auto argFrom = getRegisterArgument();

        if (!argFrom.pos)
        {
            LOGE("Offset %04x: is not a position (reg 0x%02x)", argFrom.offset, argFrom.reg);
            return false;
        }

        posFrom.init(argFrom.ptr[0], argFrom.ptr[1]);
    }

    m_registers[Asm::Register::R2] = static_cast<int16_t>(Math::distanceTo(posFrom, posTo));

    int16_t fakeDst = 0;
    setDstAndFlags(&fakeDst, m_registers[Asm::Register::R2]);

    return true;
}

bool VirtualMachine::ret(bool& exit)
{
    if (m_callstack.empty())
    {
        exit = true;
        return true;
    }

    exit = false;
    setPos(m_callstack.back());
    m_callstack.pop_back();
    return true;
}

bool VirtualMachine::commandPositionArg(int8_t cmd)
{
    auto cmdPos = pos() - 1;
    auto arg = getRegisterArgument();

    if (!arg.pos)
    {
        LOGE("Offset %04x: the argument is not a position (reg 0x%02x)", arg.offset, arg.reg);
        return false;
    }

    Position pos(arg.ptr[0], arg.ptr[1]);

    switch (cmd)
    {
        case Asm::BCode::CMOV: setCommand(Command::MovePos, pos, Target::None); break;
        case Asm::BCode::CATT: setCommand(Command::Attack, pos, Target::Ant); break;
        case Asm::BCode::CFD:  setCommand(Command::Feed, pos, Target::Food); break;
        case Asm::BCode::CTKF: setCommand(Command::TakeFood, pos, Target::Food); break;
        case Asm::BCode::CCTR: setCommand(Command::Cater, pos, Target::Ant); break;
        default:
            LOGE("Command %02x (%04x): Undefined the position command", (int)cmd, cmdPos);
            SU_BREAKPOINT();
            return false;
    }

    return true;
}

bool VirtualMachine::commandNoArgs(int8_t cmd)
{
    auto cmdPos = pos() - 1;

    switch (cmd)
    {
        case Asm::BCode::CEAT: setCommand(Command::Eat, m_ant->position(), Target::None); break;
        case Asm::BCode::CCSL: setCommand(Command::CreateSolder, m_ant->position(), Target::None); break;
        case Asm::BCode::CCWR: setCommand(Command::CreateWorker, m_ant->position(), Target::None); break;
        default:
            LOGE("Command %02x (%04x): Undefined the command", (int)cmd, cmdPos);
            SU_BREAKPOINT();
            return false;
    }
    return true;
}

bool VirtualMachine::mapSize()
{
    auto cmdPos = pos() - 1;
    auto arg = getRegisterArgument();

    if (!arg.pos)
    {
        LOGE("Offset %04x: the argument is not a position (reg 0x%02x)", arg.offset, arg.reg);
        return false;
    }

    m_map->size().store(arg.ptr);
    return true;
}

void VirtualMachine::setDstAndFlags(int16_t* dst, int32_t value)
{
    *dst = value & 0xffff;

    setRF(Asm::Register::ZF, *dst == 0);
    setRF(Asm::Register::OF, !!(value & 0xffff0000));
    setRF(Asm::Register::SF, !!(*dst & 0x8000));
}

bool VirtualMachine::checkLVal(const VirtualMachine::Argument& arg)
{
    if (!arg.ptr)
    {
        LOGE("Offset %04x: the pointer is null (reg 0x%02x)", arg.offset, arg.reg);
        return false;
    }

    if (arg.ptr)
    {
        if (arg.adr && arg.ptr <= m_memory.data())
        {
            LOGE("Offset %04x: the address 0x%04x is fault", arg.offset, m_registers[arg.reg]);
            return false;
        }
    }

    return true;
}

bool VirtualMachine::bsf(int16_t* bitno, int16_t src)
{
    if (!src)
    {
        *bitno = -1;
        return true;
    }

    for (*bitno = 0; *bitno < 16; ++*bitno)
    {
        if (src & (1 << (*bitno)))
        {
            return true;
        }
    }

    SU_BREAKPOINT();
    *bitno = 17;
    return false;
}

bool VirtualMachine::bsr(int16_t* bitno, int16_t src)
{
    if (!src)
    {
        *bitno = -1;
        return true;
    }

    for (*bitno = 15; *bitno >= 0; --*bitno)
    {
        if (src & (1 << (*bitno)))
        {
            return true;
        }
    }

    SU_BREAKPOINT();
    *bitno = 17;
    return false;
}

bool VirtualMachine::bitTest(uint8_t cmd, int16_t* dst, int16_t src)
{
    uint16_t mask = 1 << (src & 0x0f);
    bool out = !(*dst & mask);

    switch (cmd)
    {
        case Asm::BCode::BT: break;
        case Asm::BCode::BTR: *dst &= ~mask; break;
        case Asm::BCode::BTS: *dst |=  mask; break;
        case Asm::BCode::BTC: *dst ^=  mask; break;
    }

    return out;
}

bool VirtualMachine::shiftLeft(bool restore, int16_t* dst, int16_t src)
{
    src = src & 0x0f;

    if (!src)
    {
        *dst = restore ? *dst : 0;
        return false;
    }

    su::UniInt32 tmp = { 0 };
    tmp.i16[0] = *dst;
    tmp.u32 <<= src;
    *dst = tmp.i16[0];

    if (restore)
    {
        *dst |= tmp.i16[1];
    }
    return !(tmp.i32 & 0x00010000);
}

bool VirtualMachine::shiftRight(bool restore, int16_t* dst, int16_t src)
{
    src = src & 0x0f;

    if (!src)
    {
        *dst = restore ? *dst : 0;
        return false;
    }

    su::UniInt32 tmp = { 0 };
    tmp.i16[1] = *dst;
    tmp.u32 >>= src; // for signed integers, the right shift fills the bits to the right as the sign bit
                     // Therefore we using the unsigned integers
    *dst = tmp.i16[1];

    if (restore)
    {
        *dst |= tmp.i16[0];
    }
    return !(tmp.i32 & 0x00008000);
}

bool VirtualMachine::loadReceivedData(int16_t value)
{
    bool error = value < 0 || value >= m_ant->receivedData().size();

    setRF(Asm::Register::ZF, error);

    if (error)
    {
        return true;
    }

    m_memory[Memory::ReceivedData0] = m_ant->receivedData()[value].i16[0];
    m_memory[Memory::ReceivedData1] = m_ant->receivedData()[value].i16[1];
    m_memory[Memory::ReceivedData2] = m_ant->receivedData()[value].i16[2];
    //TODO m_memory[Memory::ReceivedData3] = m_ant->receivedData()[value].i16[3];

    return true;
}

bool VirtualMachine::loadFood(int16_t value)
{
    bool error = value < 0 || value >= m_foods.size();

    setRF(Asm::Register::ZF, error);

    if (error)
    {
        return true;
    }

    m_memory[Memory::FoodCount] = m_foods[value].count;
    m_memory[Memory::FoodCoordX] = m_foods[value].pos.x();
    m_memory[Memory::FoodCoordY] = m_foods[value].pos.y();

    return true;
}

bool VirtualMachine::loadAlly(int16_t value)
{
    bool error = value < 0 || value >= m_allies.size();

    setRF(Asm::Register::ZF, error);

    if (error)
    {
        return true;
    }

    int16_t type = ((int16_t)m_allies[value]->type()) << 12;
    m_memory[Memory::AllyType] = (int16_t(m_allies[value]->healthPercent() * 10)) | type;
    m_memory[Memory::AllyCoordX] = m_allies[value]->position().x();
    m_memory[Memory::AllyCoordY] = m_allies[value]->position().y();
    m_memory[Memory::AllySatiety] = m_allies[value]->satietyPercent() * 10;

    return true;
}

bool VirtualMachine::loadEnemy(int16_t value)
{
    bool error = value < 0 || value >= m_enemies.size();

    setRF(Asm::Register::ZF, error);

    if (error)
    {
        return true;
    }

    int16_t type = ((int16_t)m_enemies[value]->type()) << 12;
    m_memory[Memory::EnemyType] = (int16_t)(m_enemies[value]->healthPercent() * 10) | type;
    m_memory[Memory::EnemyCoordX] = m_enemies[value]->position().x();
    m_memory[Memory::EnemyCoordY] = m_enemies[value]->position().y();

    return true;
}

bool VirtualMachine::printDebug(int16_t value)
{
    if (!m_conf->bcodeDebug())
    {
        return true;
    }

    std::string filename = su::Log::instance().getDir() + "/" + m_conf->UBID() + ".debug.txt";

    std::ofstream file(filename, std::ios_base::app);

    if (!file.is_open())
    {
        LOGE("Error: Can't open file for debug output");
        return false;
    }

    auto player = m_ant->player();

    std::time_t t = std::time(nullptr);
    std::tm dt;

    file << "----------------------------------------------------------------------------------------" << std::endl;

    localtime_s(&dt, &t);
    file << su::String_format2("%04i.%02i.%02i %02i:%02i:%02i #%i, UserData: %i %04x",
            dt.tm_year + 1900, dt.tm_mon + 1, dt.tm_mday,
            dt.tm_hour, dt.tm_min, dt.tm_sec,
            *(uint32_t*)&m_memory[Memory::Iteration], value, value)
        << std::endl;
    file << std::endl;
    file << su::String_format2("    Player: %02i, file: '%s', Ant: %s %s",
            player->index(),
            player->library().c_str(),
            m_ant->typeToString().c_str(),
            m_ant->position().toString().c_str())
        << std::endl;
    file << std::endl;
    file << su::String_format2("    r0: %04x, r1: %04x, r2: %04x, rc: %04x, rf: %04x",
            m_registers[Asm::Register::R0], m_registers[Asm::Register::R1], m_registers[Asm::Register::R2],
            m_registers[Asm::Register::RC], m_registers[Asm::Register::RF])
        << std::endl;
    file << su::String_format2("    p0: <%04x:%04x>, p1: <%04x:%04x>, p2: <%04x:%04x>",
        m_registers[Asm::Register::P0X], m_registers[Asm::Register::P0Y],
        m_registers[Asm::Register::P1X], m_registers[Asm::Register::P1Y],
        m_registers[Asm::Register::P2X], m_registers[Asm::Register::P2Y])
        << std::endl;
    file << std::endl;
    file << su::String_printfHexBuffer(m_memory.data(), m_memory.size(), sizeof(short), "    ") << std::endl;

    file.close();

    return true;
}

};
