#include "Statement.h"

#include "stringex.h"
#include "uniint.h"

#include "defines.h"

#include "code.h"
#include "expression.h"

static void print2Expr(std::ofstream& file, const std::string& name, WarAnts::Asm::Expression* dst, WarAnts::Asm::Expression* src)
{
    file << name << " " << dst->toString() << ", " << src->toString();
}

static void print1Expr(std::ofstream& file, const std::string& name, WarAnts::Asm::Expression* dst)
{
    file << name << " " << dst->toString();
}

static void print0Expr(std::ofstream& file, const std::string& name)
{
    file << name;
}

static void printLabel(std::ofstream& file, const std::string& name, const std::string& label)
{
    file << name << " " << label;
}

namespace WarAnts
{
namespace Asm
{

namespace Table
{

//                         R i g h t
//                       V  R  P  [] <>
CheckTable LVal     = { {0, 0, 0, 0, 0},   // value   L
                        {1, 1, 0, 1, 0},   // reg     e
                        {1, 1, 1, 1, 1},   // pos     f
                        {1, 1, 0, 1, 0},   // []      t
                        {1, 1, 1, 1, 1} }; // <>

CheckTable LValNP   = { {0, 0, 0, 0, 0},   // value
                        {1, 1, 0, 1, 0},   // reg
                        {0, 0, 0, 0, 0},   // pos
                        {1, 1, 0, 1, 0},   // []
                        {0, 0, 0, 0, 0} }; // <>

CheckTable RVal     = { {1, 0, 0, 0, 0},   // value   L
                        {0, 1, 0, 0, 0},   // reg     e
                        {0, 0, 1, 0, 0},   // pos     f
                        {0, 0, 0, 1, 0},   // []      t
                        {0, 0, 0, 0, 1} }; // <>

CheckTable RValNP   = { {1, 0, 0, 0, 0},   // value   L
                        {0, 1, 0, 0, 0},   // reg     e
                        {0, 0, 0, 0, 0},   // pos     f
                        {0, 0, 0, 1, 0},   // []      t
                        {0, 0, 0, 0, 0} }; // <>

CheckTable Strong   = { {0, 0, 0, 0, 0},   // value   L
                        {1, 1, 0, 1, 0},   // reg     e
                        {0, 0, 1, 0, 1},   // pos     f
                        {1, 1, 0, 1, 0},   // []      t
                        {0, 0, 1, 0, 1} }; // <>

CheckTable Position = { {0, 0, 0, 0, 0},   // value
                        {0, 0, 0, 0, 0},   // reg
                        {0, 0, 1, 0, 1},   // pos
                        {0, 0, 0, 0, 0},   // []
                        {0, 0, 1, 0, 1} }; // <>

static uint8_t regToIndex(uint8_t reg)
{
    if (reg & Register::ADDRESS)
    {
        return reg & Register::POSITION ? 4 : 3;
    }
    if ((reg & Register::COUNT) == Register::CHAR || (reg & Register::COUNT) == Register::SHORT)
    {
        return 0;
    }

    return reg & Register::POSITION ? 2 : 1;
}


static bool check(uint8_t left, uint8_t right, const CheckTable& table)
{
    return table[regToIndex(left)][regToIndex(right)];
}
} //namespace Table

bool Statement::isJump() const
{
    return type() == StatementType::Command &&
        (m_cmd == AsmCommand::JMP  ||
         m_cmd == AsmCommand::JZ   ||
         m_cmd == AsmCommand::JNZ  ||
         m_cmd == AsmCommand::JO   ||
         m_cmd == AsmCommand::JNO  ||
         m_cmd == AsmCommand::JS   ||
         m_cmd == AsmCommand::JNS  ||
         m_cmd == AsmCommand::JCZ  ||
         m_cmd == AsmCommand::JCNZ ||
         m_cmd == AsmCommand::LOOP ||
         m_cmd == AsmCommand::CALL);
}

bool Statement::isCall() const
{
    return isJump() && m_cmd == AsmCommand::CALL;
}

int16_t Statement::jumpValue() const
{
    su::UniInt16 out = { 0 };

    if (!isJump())
    {
        return out.i16;
    }

    out.i8[0] = m_bcode[1];
    if ((m_bcode[0] & BCode::JUMP_MASK) == BCode::JUMP_SHORT)
    {
        out.i8[1] = m_bcode[2];
        return out.i16;
    }

    return out.i8[0];
}

bool Statement::checkUnusedJump() const
{
    if (!isJump())
    {
        return false;
    }

    if ((m_bcode[0] & BCode::JUMP_SHORT) == 0)
    {
        return m_bcode[1] == 2;
    }

    return false;
}

bool Statement::isReturn() const
{
    return type() == StatementType::Command && m_cmd == AsmCommand::RET;
}

bool Statement::isValueCommand() const
{
    int8_t tv = BCode::TYPE_VALUE;
    return m_bcode.size() && ((m_bcode[0] & tv) == tv);
}

Statement* Statement::extrudeExpression(Code* code)
{
    Statement* out = nullptr;
    Statement* statDst = nullptr;
    Statement* statSrc = nullptr;

    if (m_dst)
    {
        if (m_dst->type() == ExpressionType::Number)
        {
            code->error(lineno(), "Numbers can not be using as destination.");
            return nullptr;
        }

        if (m_dst->type() == ExpressionType::Register)
        {
            if (m_dst->reg() == Register::RF)
            {
                code->error(lineno(), "Register `RF` can not be using as destination.");
            }

            return nullptr;
        }

        statDst = m_dst->extrudeExpression(true, code);
        if (code->hasError())
        {
            return nullptr;
        }
    }

    if (m_src)
    {
        statSrc = m_src->extrudeExpression(false, code);
        if (code->hasError())
        {
            return nullptr;
        }
    }

    if (statDst && statSrc)
    {
        statDst->add(statSrc);
        return statDst;
    }

    return statDst ? statDst : statSrc;
}

bool Statement::compile(Code* code)
{
    m_offset = code->offset();

    if (type() == StatementType::Label)
    {
        return true;
    }

    switch (m_cmd)
    {
        case AsmCommand::ADD:  compile2Args(BCode::ADD, Table::LVal,   code); break;
        case AsmCommand::AND:  compile2Args(BCode::AND, Table::LValNP, code); break;
        case AsmCommand::DEC:  compile1Args(BCode::DEC, Table::LVal,   code); break;
        case AsmCommand::DIV:  compile2Args(BCode::DIV, Table::LVal,   code); break;
        case AsmCommand::INC:  compile1Args(BCode::INC, Table::LVal,   code); break;
        case AsmCommand::MOD:  compile2Args(BCode::MOD, Table::LValNP, code); break;
        case AsmCommand::MUL:  compile2Args(BCode::MUL, Table::LVal,   code); break;
        case AsmCommand::NEG:  compile1Args(BCode::NEG, Table::LVal,   code); break;
        case AsmCommand::NOT:  compile1Args(BCode::NOT, Table::LValNP, code); break;
        case AsmCommand::OR:   compile2Args(BCode::OR,  Table::LValNP, code); break;
        case AsmCommand::SUB:  compile2Args(BCode::SUB, Table::LVal,   code); break;
        case AsmCommand::XOR:  compile2Args(BCode::XOR, Table::LValNP, code); break;
        case AsmCommand::MIN:  compile2Args(BCode::MIN, Table::LVal,   code); break;
        case AsmCommand::MAX:  compile2Args(BCode::MAX, Table::LVal,   code); break;

        case AsmCommand::BSF:  compile2Args(BCode::BSF,  Table::LValNP, code); break;
        case AsmCommand::BSR:  compile2Args(BCode::BSR,  Table::LValNP, code); break;
        case AsmCommand::BT:   compile2Args(BCode::BT,   Table::LValNP, code); break;
        case AsmCommand::BTR:  compile2Args(BCode::BTR,  Table::LValNP, code); break;
        case AsmCommand::BTS:  compile2Args(BCode::BTS,  Table::LValNP, code); break;
        case AsmCommand::BTC:  compile2Args(BCode::BTC,  Table::LValNP, code); break;
        case AsmCommand::SHL:  compile2Args(BCode::SHL,  Table::LValNP, code); break;
        case AsmCommand::SHR:  compile2Args(BCode::SHR,  Table::LValNP, code); break;
        case AsmCommand::ROL:  compile2Args(BCode::ROL,  Table::LValNP, code); break;
        case AsmCommand::ROR:  compile2Args(BCode::ROR,  Table::LValNP, code); break;

        case AsmCommand::EQ:   compile2Args(BCode::EQ,   Table::Strong, code); break;
        case AsmCommand::NEQ:  compile2Args(BCode::NEQ,  Table::Strong, code); break;
        case AsmCommand::GT:   compile2Args(BCode::GT,   Table::LValNP, code); break;
        case AsmCommand::GE:   compile2Args(BCode::GE,   Table::LValNP, code); break;
        case AsmCommand::LT:   compile2Args(BCode::LT,   Table::LValNP, code); break;
        case AsmCommand::LE:   compile2Args(BCode::LE,   Table::LValNP, code); break;
        case AsmCommand::TEST: compile2Args(BCode::TEST, Table::LValNP, code); break;

        case AsmCommand::JMP:  compileJump(BCode::JMP,  code); break;
        case AsmCommand::JZ:   compileJump(BCode::JZ,   code); break;
        case AsmCommand::JNZ:  compileJump(BCode::JNZ,  code); break;
        case AsmCommand::JO:   compileJump(BCode::JO,   code); break;
        case AsmCommand::JNO:  compileJump(BCode::JNO,  code); break;
        case AsmCommand::JS:   compileJump(BCode::JS,   code); break;
        case AsmCommand::JNS:  compileJump(BCode::JNS,  code); break;
        case AsmCommand::JCZ:  compileJump(BCode::JCZ,  code); break;
        case AsmCommand::JCNZ: compileJump(BCode::JCNZ, code); break;
        case AsmCommand::LOOP: compileJump(BCode::LOOP, code); break;
        case AsmCommand::CALL: compileJump(BCode::CALL, code); break;

        case AsmCommand::MOV:  compile2Args(BCode::MOV,  Table::LVal,     code); break;
        case AsmCommand::LEN:  compile2Args(BCode::LEN,  Table::Position, code); break;
        case AsmCommand::DIST: compile1Args(BCode::DIST, Table::Position, code); break;
        case AsmCommand::RET:  compileNoArgs(BCode::RET, code); break;
        case AsmCommand::DBG:  compile1Args(BCode::DBG, Table::RVal,      code); break;
        case AsmCommand::MPSZ: compile1Args(BCode::MPSZ, Table::Position, code); break;

        case AsmCommand::LDRC: compile1Args(BCode::LDRC, Table::RValNP, code); break;
        case AsmCommand::LDFD: compile1Args(BCode::LDFD, Table::RValNP, code); break;
        case AsmCommand::LDEN: compile1Args(BCode::LDEN, Table::RValNP, code); break;
        case AsmCommand::LDAL: compile1Args(BCode::LDAL, Table::RValNP, code); break;

        case AsmCommand::CIDL: compile1Args(BCode::CIDL, Table::RValNP,   code); break;
        case AsmCommand::CMOV: compile1Args(BCode::CMOV, Table::Position, code); break;
        case AsmCommand::CATT: compile1Args(BCode::CATT, Table::Position, code); break;
        case AsmCommand::CFD:  compile1Args(BCode::CFD,  Table::Position, code); break;
        case AsmCommand::CTKF: compile1Args(BCode::CTKF, Table::Position, code); break;
        case AsmCommand::CCSL: compileNoArgs(BCode::CCSL, code); break;
        case AsmCommand::CCWR: compileNoArgs(BCode::CCWR, code); break;

        case AsmCommand::NOP:  compileNoArgs(BCode::NOP, code); break;

        default:
            SU_BREAKPOINT();
            return false;
    }

    return !code->hasError();
}

bool Statement::optimizeValueStatement(Code* code)
{
    if (!isValueCommand())
    {
        return true;
    }

    if (m_bcode[1] == Register::CHAR)
    {
        m_bcode[0] |= BCode::VALUE_CHAR;
        m_bcode[1] = m_bcode[2];
        m_bcode.pop_back();
    }
    else if (m_bcode[1] == Register::SHORT)
    {
        m_bcode[0] |= BCode::VALUE_SHORT;
        m_bcode[1] = m_bcode[2];
        m_bcode[2] = m_bcode[3];
        m_bcode.pop_back();
    }

    return true;
}

bool Statement::assignOffsets(Code* code)
{
    m_offset = code->updateOffset((int16_t)m_bcode.size());
    return true;
}

bool Statement::resolveLabels(bool& recalc, Code* code)
{
    if (!isJump())
    {
        return true;
    }

    if (!m_labelPtr)
    {
        SU_BREAKPOINT();
        return false;
    }

    int32_t curDelta32 = int32_t(m_labelPtr->offset() - m_offset);
    int16_t oldDelta = jumpValue();
    if (curDelta32 < -32768 || curDelta32 > 32767)
    {
        SU_BREAKPOINT();
        code->error(lineno(), "Fatal error: The jump value great at int16");
        return false;
    }

    int16_t curDelta = curDelta32;
    bool isFar = curDelta  < -128 || curDelta > 127;
    bool isChanged = curDelta != oldDelta;
    size_t newSize = 2 + (size_t)isFar;
    recalc |= newSize != m_bcode.size() || isChanged;
    if (newSize > m_bcode.size())
    {
        m_bcode[0] |= BCode::JUMP_SHORT;
        m_bcode.push_back(0);
    }
    else if (newSize < m_bcode.size())
    {
        m_bcode[0] &= ~(BCode::JUMP_SHORT);
        m_bcode.pop_back();
    }

    if (!isFar)
    {
        m_bcode[1] = (int8_t)curDelta;
    }
    else
    {
        su::UniInt16 offset = { curDelta };
        
        m_bcode[1] = offset.i8[0];
        m_bcode[2] = offset.i8[1];
    }
    return true;
}

bool Statement::save(Code* code)
{
    if (type() == StatementType::Label)
    {
        return true;
    }

    if (m_bcode.empty())
    {
        return false;
    }

    for (auto val : m_bcode)
    {
        code->addCode(val);
    }
    return true;
}

void Statement::print(std::ofstream& file) const
{
    if (m_type == StatementType::Label)
    {
        file << m_label << ":" << std::endl;
        return;
    }

    file << "\t";
    switch (m_cmd)
    {
        case AsmCommand::ADD:  print2Expr(file, "ADD ", m_dst, m_src); break;
        case AsmCommand::AND:  print2Expr(file, "AND ", m_dst, m_src); break;
        case AsmCommand::DEC:  print1Expr(file, "DEC ", m_dst); break;
        case AsmCommand::DIV:  print2Expr(file, "DIV ", m_dst, m_src); break;
        case AsmCommand::INC:  print1Expr(file, "INC ", m_dst); break;
        case AsmCommand::MOD:  print2Expr(file, "MOD ", m_dst, m_src); break;
        case AsmCommand::MUL:  print2Expr(file, "MUL ", m_dst, m_src); break;
        case AsmCommand::NEG:  print1Expr(file, "NEG ", m_dst); break;
        case AsmCommand::NOT:  print1Expr(file, "NOT ", m_dst); break;
        case AsmCommand::OR:   print2Expr(file, "OR  ", m_dst, m_src); break;
        case AsmCommand::SUB:  print2Expr(file, "SUB ", m_dst, m_src); break;
        case AsmCommand::XOR:  print2Expr(file, "XOR ", m_dst, m_src); break;
        case AsmCommand::MIN:  print2Expr(file, "MIN ", m_dst, m_src); break;
        case AsmCommand::MAX:  print2Expr(file, "MAX ", m_dst, m_src); break;

        case AsmCommand::BSF:  print2Expr(file, "BSF ", m_dst, m_src); break;
        case AsmCommand::BSR:  print2Expr(file, "BSR ", m_dst, m_src); break;
        case AsmCommand::BT:   print2Expr(file, "BT  ", m_dst, m_src); break;
        case AsmCommand::BTR:  print2Expr(file, "BTR ", m_dst, m_src); break;
        case AsmCommand::BTS:  print2Expr(file, "BTS ", m_dst, m_src); break;
        case AsmCommand::BTC:  print2Expr(file, "BTC ", m_dst, m_src); break;
        case AsmCommand::SHL:  print2Expr(file, "SHL ", m_dst, m_src); break;
        case AsmCommand::SHR:  print2Expr(file, "SHR ", m_dst, m_src); break;
        case AsmCommand::ROL:  print2Expr(file, "ROL ", m_dst, m_src); break;
        case AsmCommand::ROR:  print2Expr(file, "ROR ", m_dst, m_src); break;

        case AsmCommand::EQ:   print2Expr(file, "EQ  ", m_dst, m_src); break;
        case AsmCommand::NEQ:  print2Expr(file, "NEQ ", m_dst, m_src); break;
        case AsmCommand::GT:   print2Expr(file, "GT  ", m_dst, m_src); break;
        case AsmCommand::GE:   print2Expr(file, "GE  ", m_dst, m_src); break;
        case AsmCommand::LT:   print2Expr(file, "LT  ", m_dst, m_src); break;
        case AsmCommand::LE:   print2Expr(file, "LE  ", m_dst, m_src); break;
        case AsmCommand::TEST: print2Expr(file, "TEST", m_dst, m_src); break;

        case AsmCommand::JMP:  printLabel(file, "JMP ", m_label); break;
        case AsmCommand::JZ:   printLabel(file, "JZ  ", m_label); break;
        case AsmCommand::JNZ:  printLabel(file, "JNZ ", m_label); break;
        case AsmCommand::JO:   printLabel(file, "JO  ", m_label); break;
        case AsmCommand::JNO:  printLabel(file, "JNO ", m_label); break;
        case AsmCommand::JS:   printLabel(file, "JS  ", m_label); break;
        case AsmCommand::JNS:  printLabel(file, "JNS ", m_label); break;
        case AsmCommand::JCZ:  printLabel(file, "JCZ ", m_label); break;
        case AsmCommand::JCNZ: printLabel(file, "JCNZ", m_label); break;
        case AsmCommand::LOOP: printLabel(file, "LOOP", m_label); break;
        case AsmCommand::CALL: printLabel(file, "CALL", m_label); break;

        case AsmCommand::MOV:  print2Expr(file, "MOV ", m_dst, m_src); break;
        case AsmCommand::LEN:  print2Expr(file, "LEN ", m_dst, m_src); break;
        case AsmCommand::DIST: print1Expr(file, "DIST", m_dst       ); break;
        case AsmCommand::RET:  print0Expr(file, "RET"); break;
        case AsmCommand::DBG:  print1Expr(file, "DBG",  m_src); break;
        case AsmCommand::MPSZ: print1Expr(file, "MPSZ", m_dst); break;

        case AsmCommand::LDRC: print1Expr(file, "LDRC", m_src); break;
        case AsmCommand::LDFD: print1Expr(file, "LDFD", m_src); break;
        case AsmCommand::LDEN: print1Expr(file, "LDEN", m_src); break;
        case AsmCommand::LDAL: print1Expr(file, "LDAL", m_src); break;

        case AsmCommand::CIDL: print1Expr(file, "CIDL", m_src); break;
        case AsmCommand::CMOV: print1Expr(file, "CMOV", m_dst); break;
        case AsmCommand::CATT: print1Expr(file, "CATT", m_dst); break;
        case AsmCommand::CTKF: print1Expr(file, "CTKF", m_dst); break;
        case AsmCommand::CGVF: print1Expr(file, "CGVF", m_dst); break;
        case AsmCommand::CEAT: print1Expr(file, "CEAT", m_src); break;
        case AsmCommand::CCSL: print0Expr(file, "CCSL"); break;
        case AsmCommand::CCWR: print0Expr(file, "CCWR"); break;

        case AsmCommand::NOP:  print0Expr(file, "NOP"); break;
        default:
            file << "UNDEFINE COMMAND " << (uint32_t)m_cmd << std::endl;
            return;
    }

    if (m_bcode.size())
    {
        file << "    ; " << su::String_format2("[%04x]", offset());
        
        for (auto item : m_bcode)
        {
            int32_t val = item;
            val &= 0xff;
            file << su::String_format2(" %02x", val);
        }
    }

    file << std::endl;
}

uint8_t Statement::compileExpr(Expression* expr, Code* code)
{
    su::UniInt16 val = { 0 };
    uint8_t reg = expr->compile(val.i16, code);
    
    if (code->hasError())
    {
        return Register::INVALIDE;
    }

    uint8_t clearReg = reg & Register::COUNT;
    m_bcode.push_back(reg);

    if (clearReg == Register::CHAR)
    {
        m_bcode.push_back(val.i8[0]);
    }

    if (clearReg == Register::SHORT)
    {
        m_bcode.push_back(val.i8[0]);
        m_bcode.push_back(val.i8[1]);
    }

    return reg;
}

void Statement::compileNoArgs(BCode::Command cmd, Code* code)
{
    m_bcode.push_back((int8_t)cmd);
}

void Statement::compile2Args(BCode::Command cmd, const Table::CheckTable& table, Code* code)
{
    m_bcode.push_back((int8_t)cmd);
    Register::Type dst = (Register::Type)compileExpr(m_dst, code);
    Register::Type src = (Register::Type)compileExpr(m_src, code);

    if (!Table::check(dst, src, table))
    {
        code->error(lineno(), "The left and the right arguments are not compatible.");
    }
}

void Statement::compile1Args(BCode::Command cmd, const Table::CheckTable& table, Code* code)
{
    m_bcode.push_back((int8_t)cmd);
    Register::Type dst = (Register::Type)compileExpr(m_dst ? m_dst : m_src, code);

    if (!Table::check(dst, dst, table))
    {
        code->error(lineno(), "This arguments and the command are not compatible.");
    }
}

void Statement::compileJump(BCode::Command cmdl, Code* code)
{
    m_bcode.push_back((int8_t)cmdl | BCode::JUMP_SHORT);
    m_bcode.push_back(0);
    m_bcode.push_back(0);
}

} // namespace Asm
} // namespace WarAnts
