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
    m_ant = ant;
    m_map = map;

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
        UniInt16 val = { 0 };
        val.i8[0] = m_bcode[m_pos++];
        val.i8[1] = m_bcode[m_pos++];
        m_registers[Asm::Register::SHORT] = val.i16;
    }

    if (out.adr)
    {
        if (m_registers[out.reg] >= m_memory.size())
        {
            LOGE("Command %02x (%04x): invalide address 0x04x",
                m_bcode[m_pos - 2], m_pos - 1, m_registers[out.reg]);
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
            UniInt16 offset = { 0 };

            valType = cmd & Asm::BCode::JUMP_MASK;
            cmd &= ~Asm::BCode::JUMP_MASK;
            

            if (valType == Asm::BCode::JUMP_SHORT)
            {
                offset.i8[0] = getNextChar();
                offset.i8[1] = getNextChar();
            }
            else
            {
                offset.i16 = getNextChar();
            }
            value = offset.i16;
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

//                LDTR = 0x60,
            case Asm::BCode::LDFD: result = loadFood(value); break;
//                LDEN = 0x68,
//                LDFR = 0x6c,
//                CIDL = 0x70,
//                CEAT = 0x74,
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

#define CHECK_PTR(x)            if (!(x).ptr) { return false; }
#define CHECK_LVAL(x)           if (!(x).ptr && !checkLVal(x)) { return false; }

bool VirtualMachine::arithmetic1(uint8_t cmd)
{
    auto cmdPos = pos();
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
    auto cmdPos = pos();
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
    auto cmdPos = pos();
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
    auto cmdPos = pos();

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
    auto cmdPos = pos();
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

void VirtualMachine::setDstAndFlags(int16_t* dst, int32_t value)
{
    *dst = value & 0xffff;

    setRF(Asm::Register::ZF, *dst == 0);
    setRF(Asm::Register::OF, !!(value & 0xffff0000));
    setRF(Asm::Register::SF, !!(*dst & 0x8000));
}

bool VirtualMachine::checkLVal(const VirtualMachine::Argument& arg)
{
    if (arg.adr && m_registers[arg.reg] <= Memory::ReadOnly)
    {
        LOGE("Offset %04x: the address 0x04x is readonly", arg.offset, m_registers[arg.reg]);
        return false;
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

    UniInt32 tmp = { 0 };
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

    UniInt32 tmp = { 0 };
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

bool VirtualMachine::loadFood(int16_t value)
{
    bool error = value < 0 || value >= m_foods.size();

    setRF(Asm::Register::ZF, error);

    if (error)
    {
        return true;
    }

    m_memory[Memory::FoodCoord_X] = m_foods[value].x();
    m_memory[Memory::FoodCoord_Y] = m_foods[value].y();

    return true;
}

};
