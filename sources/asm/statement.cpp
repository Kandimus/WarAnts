#include "Statement.h"

#include "stringex.h"

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

bool Statement::isJump() const
{
    return type() == StatementType::Command &&
        (m_cmd == AsmCommand::JMP ||
         m_cmd == AsmCommand::JZ ||
         m_cmd == AsmCommand::JNZ ||
         m_cmd == AsmCommand::JO ||
         m_cmd == AsmCommand::JNO ||
         m_cmd == AsmCommand::JCZ ||
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
    if (!isJump())
    {
        return 0;
    }

    return (m_bcode[0] & (int32_t)BCodeJump::SHORT)
     ? m_bcode[1] + m_bcode[2] * 256
     : m_bcode[1];
}

bool Statement::checkUnusedJump() const
{
    if (!isJump())
    {
        return false;
    }

    if ((m_bcode[0] & (int8_t)BCodeJump::SHORT) == 0)
    {
        return m_bcode[1] == 2;
    }

    return false;
}

bool Statement::isExit() const
{
    return type() == StatementType::Command && m_cmd == AsmCommand::EXIT;
}

bool Statement::isValueCommand() const
{
    int8_t tv = (int8_t)BCodeType::VALUE;
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
            if (m_dst->reg() == RegisterType::RF)
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
        case AsmCommand::ADD:  compileCommon(BCodeCommand::ADD, code); break;
        case AsmCommand::AND:  compileNoPosition(BCodeCommand::AND, code); break;
        case AsmCommand::DEC:  compileDstCommon(BCodeCommand::DEC, code); break;
        case AsmCommand::DIV:  compileCommon(BCodeCommand::DIV, code); break;
        case AsmCommand::INC:  compileDstCommon(BCodeCommand::INC, code); break;
        case AsmCommand::MOD:  compileNoPosition(BCodeCommand::MOD, code); break;
        case AsmCommand::MUL:  compileCommon(BCodeCommand::MUL, code); break;
        case AsmCommand::NEG:  compileDstCommon(BCodeCommand::NEG, code); break;
        case AsmCommand::NOT:  compileDstNoPosition(BCodeCommand::NOT, code); break;
        case AsmCommand::OR:   compileNoPosition(BCodeCommand::OR, code); break;
        case AsmCommand::SUB:  compileCommon(BCodeCommand::SUB, code); break;
        case AsmCommand::XOR:  compileNoPosition(BCodeCommand::XOR, code); break;
        case AsmCommand::MIN:  compileStrong(BCodeCommand::MIN, code); break;
        case AsmCommand::MAX:  compileStrong(BCodeCommand::MAX, code); break;

        case AsmCommand::BSF:  compileNoPosition(BCodeCommand::BSF, code); break;
        case AsmCommand::BSR:  compileNoPosition(BCodeCommand::BSR, code); break;
        case AsmCommand::BT:   compileNoPosition(BCodeCommand::BT,  code); break;
        case AsmCommand::BTR:  compileNoPosition(BCodeCommand::BTR, code); break;
        case AsmCommand::BTS:  compileNoPosition(BCodeCommand::BTS, code); break;
        case AsmCommand::BTC:  compileNoPosition(BCodeCommand::BTC, code); break;
        case AsmCommand::SHL:  compileNoPosition(BCodeCommand::SHL, code); break;
        case AsmCommand::SHR:  compileNoPosition(BCodeCommand::SHR, code); break;
        case AsmCommand::ROL:  compileNoPosition(BCodeCommand::ROL, code); break;
        case AsmCommand::ROR:  compileNoPosition(BCodeCommand::ROR, code); break;

        case AsmCommand::EQ:   compileStrong(BCodeCommand::EQ , code); break;
        case AsmCommand::NEQ:  compileStrong(BCodeCommand::NEQ, code); break;
        case AsmCommand::GT:   compileNoPosition(BCodeCommand::GT  , code); break;
        case AsmCommand::GE:   compileNoPosition(BCodeCommand::GE  , code); break;
        case AsmCommand::LT:   compileNoPosition(BCodeCommand::LT  , code); break;
        case AsmCommand::LE:   compileNoPosition(BCodeCommand::LE  , code); break;
        case AsmCommand::TEST: compileNoPosition(BCodeCommand::TEST, code); break;

        case AsmCommand::JMP:  compileJump(BCodeCommand::JMPl, code); break;
        case AsmCommand::JZ:   compileJump(BCodeCommand::JZl, code); break;
        case AsmCommand::JNZ:  compileJump(BCodeCommand::JNZl, code); break;
        case AsmCommand::JO:   compileJump(BCodeCommand::JOl, code); break;
        case AsmCommand::JNO:  compileJump(BCodeCommand::JNOl, code); break;
        case AsmCommand::JCZ:  compileJump(BCodeCommand::JCZl, code); break;
        case AsmCommand::JCNZ: compileJump(BCodeCommand::JCNZl, code); break;
        case AsmCommand::LOOP: compileJump(BCodeCommand::LOOPl, code); break;
        case AsmCommand::CALL: compileJump(BCodeCommand::CALLl, code); break;

        case AsmCommand::MOV:  compileCommon(BCodeCommand::MOV, code); break;
        case AsmCommand::LEN:  compilePosition(BCodeCommand::LEN, code); break;
        case AsmCommand::DIST: compileDstNoPositionSrcPosition(BCodeCommand::DIST, code); break;
        case AsmCommand::EXIT: compileNoArgs(BCodeCommand::EXIT, code); break;

        case AsmCommand::LDTR: compileSrcNoPosition(BCodeCommand::LDTR, code); break;
        case AsmCommand::LDFD: compileSrcNoPosition(BCodeCommand::LDFD, code); break;
        case AsmCommand::LDEN: compileSrcNoPosition(BCodeCommand::LDEN, code); break;
        case AsmCommand::LDFR: compileSrcNoPosition(BCodeCommand::LDFR, code); break;

        case AsmCommand::CIDL: compileSrcNoPosition(BCodeCommand::CIDL, code); break;
        case AsmCommand::CMOV: compileDstPosition(BCodeCommand::CMOV, code); break;
        case AsmCommand::CATT: compileDstPosition(BCodeCommand::CATT, code); break;
        case AsmCommand::CTKF: compileDstPosition(BCodeCommand::CTKF, code); break;
        case AsmCommand::CGVF: compileDstPosition(BCodeCommand::CGVF, code); break;
        case AsmCommand::CEAT: compileSrcNoPosition(BCodeCommand::CEAT, code); break;
        case AsmCommand::CPS:  compileNoArgs(BCodeCommand::CPS, code); break;
        case AsmCommand::CPW:  compileNoArgs(BCodeCommand::CPW, code); break;

        case AsmCommand::NOP:  compileNoArgs(BCodeCommand::NOP, code); break;

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

    if (m_bcode[1] == (int8_t)RegisterType::CHAR)
    {
        m_bcode[0] |= (int8_t)BCodeValue::CHAR;
        m_bcode[1] = m_bcode[2];
        m_bcode.pop_back();
    }
    else if (m_bcode[1] == (int8_t)RegisterType::SHORT)
    {
        m_bcode[0] |= (int8_t)BCodeValue::SHORT;
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

    int32_t curDelta = int32_t(m_labelPtr->offset() - m_offset);
    int16_t oldDelta = jumpValue();
    if (curDelta < -32768 || curDelta > 32767)
    {
        SU_BREAKPOINT();
        code->error(lineno(), "Fatal error: The jump value great at int16");
        return false;
    }

    bool isFar = curDelta  < -128 || curDelta > 127;
    bool isChanged = curDelta != oldDelta;
    size_t newSize = 2 + (size_t)isFar;
    recalc |= newSize != m_bcode.size() || isChanged;
    if (newSize > m_bcode.size())
    {
        m_bcode[0] |= (int8_t)BCodeJump::SHORT;
        m_bcode.push_back(0);
    }
    else if (newSize < m_bcode.size())
    {
        m_bcode[0] &= ~((int8_t)BCodeJump::SHORT);
        m_bcode.pop_back();
    }

    m_bcode[1] = curDelta & 0xff;
    if (isFar)
    {
        m_bcode[2] = (curDelta & 0xff00) >> 8;
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
        case AsmCommand::JCZ:  printLabel(file, "JCZ ", m_label); break;
        case AsmCommand::JCNZ: printLabel(file, "JCNZ", m_label); break;
        case AsmCommand::LOOP: printLabel(file, "LOOP", m_label); break;
        case AsmCommand::CALL: printLabel(file, "CALL", m_label); break;

        case AsmCommand::MOV:  print2Expr(file, "MOV ", m_dst, m_src); break;
        case AsmCommand::LEN:  print2Expr(file, "LEN ", m_dst, m_src); break;
        case AsmCommand::DIST: print2Expr(file, "DIST", m_dst, m_src); break;
        case AsmCommand::EXIT: print0Expr(file, "EXIT"); break;

        case AsmCommand::LDTR: print1Expr(file, "LDTR", m_src); break;
        case AsmCommand::LDFD: print1Expr(file, "LDFD", m_src); break;
        case AsmCommand::LDEN: print1Expr(file, "LDEN", m_src); break;
        case AsmCommand::LDFR: print1Expr(file, "LDFR", m_src); break;

        case AsmCommand::CIDL: print1Expr(file, "CIDL", m_src); break;
        case AsmCommand::CMOV: print1Expr(file, "CMOV", m_dst); break;
        case AsmCommand::CATT: print1Expr(file, "CATT", m_dst); break;
        case AsmCommand::CTKF: print1Expr(file, "CTKF", m_dst); break;
        case AsmCommand::CGVF: print1Expr(file, "CGVF", m_dst); break;
        case AsmCommand::CEAT: print1Expr(file, "CEAT", m_src); break;
        case AsmCommand::CPS:  print0Expr(file, "CPS"); break;
        case AsmCommand::CPW:  print0Expr(file, "CPW"); break;

        case AsmCommand::NOP:  print0Expr(file, "NOP"); break;
        default:
            file << "UNDEFINE COMMAND " << (uint32_t)m_cmd << std::endl;
            return;
    }

    if (m_bcode.size())
    {
        file << "\t\t//" << su::String_format2("[%i]", offset());
        
        for (auto item : m_bcode)
        {
            int32_t val = item;
            val &= 0xff;
            file << su::String_format2(" %02x", val);
        }
    }

    file << std::endl;
}

RegisterType Statement::compileExpr(Expression* expr, bool isDst, Code* code)
{
    Int16And8 val;
    int8_t reg = expr->compile(true, val.i16, code);
    
    if (code->hasError())
    {
        return RegisterType::INVALIDE;
    }

    RegisterType clearReg = (RegisterType)(reg & 0x7F);
    m_bcode.push_back(reg);

    if (clearReg == RegisterType::CHAR)
    {
        m_bcode.push_back(val.i8[0]);
    }

    if (clearReg == RegisterType::SHORT)
    {
        m_bcode.push_back(val.i8[0]);
        m_bcode.push_back(val.i8[1]);
    }

    return clearReg;
}

void Statement::compileDstSrc(BCodeCommand cmd, RegisterType& dst, RegisterType& src, Code* code)
{
    m_bcode.push_back((int8_t)cmd);
    dst = compileExpr(m_dst, true, code);
    src = compileExpr(m_src, false, code);
}

void Statement::compileDst(BCodeCommand cmd, RegisterType& dst, Code* code)
{
    m_bcode.push_back((int8_t)cmd);
    dst = compileExpr(m_dst, true, code);
}

void Statement::compileSrc(BCodeCommand cmd, RegisterType& src, Code* code)
{
    m_bcode.push_back((int8_t)cmd);
    src = compileExpr(m_src, false, code);
}

void Statement::compileNoArgs(BCodeCommand cmd, Code* code)
{
    m_bcode.push_back((int8_t)cmd);
}

void Statement::compileCommon(BCodeCommand cmd, Code* code)
{
    RegisterType dst;
    RegisterType src;
    compileDstSrc(cmd, dst, src, code);
}

void Statement::compileDstCommon(BCodeCommand cmd, Code* code)
{
    RegisterType dst;
    compileDst(cmd, dst, code);
}

void Statement::compileSrcCommon(BCodeCommand cmd, Code* code)
{
    RegisterType src;
    compileSrc(cmd, src, code);
}

void Statement::compileNoPosition(BCodeCommand cmd, Code* code)
{
    RegisterType dst;
    RegisterType src;
    compileDstSrc(cmd, dst, src, code);

    if (isPositionRegister(dst) || isPositionRegister(src))
    {
        code->error(lineno(), "Position register cannot be used in this statement.");
        return;
    }
 }

void Statement::compileDstNoPosition(BCodeCommand cmd, Code* code)
{
    RegisterType dst;
    compileDst(cmd, dst, code);

    if (isPositionRegister(dst))
    {
        code->error(lineno(), "Position register cannot be used in this statement.");
        return;
    }
}

void Statement::compileSrcNoPosition(BCodeCommand cmd, Code* code)
{
    RegisterType src;
    compileSrc(cmd, src, code);

    if (isPositionRegister(src))
    {
        code->error(lineno(), "Position register cannot be used in this statement.");
        return;
    }
}

void Statement::compileStrong(BCodeCommand cmd, Code* code)
{
    RegisterType dst;
    RegisterType src;
    compileDstSrc(cmd, dst, src, code);

    if (isPositionRegister(dst) == isPositionRegister(src) ||
        m_dst->type() == ExpressionType::Address ||
        m_src->type() == ExpressionType::Address)
    {
        return;
    }

    code->error(lineno(), "Only equalies types of registers must be used in this statement.");
}

void Statement::compileJump(BCodeCommand cmdl, Code* code)
{
    m_bcode.push_back((int8_t)cmdl | (int8_t)BCodeJump::SHORT);
    m_bcode.push_back(0);
    m_bcode.push_back(0);
}

void Statement::compilePosition(BCodeCommand cmd, Code* code)
{
    RegisterType dst;
    RegisterType src;
    compileDstSrc(cmd, dst, src, code);

    if ((isPositionRegister(dst) || m_dst->type() == ExpressionType::Address) &&
        (isPositionRegister(src) || m_src->type() == ExpressionType::Address))
    {
        return;
    }

    code->error(lineno(), "Only position registers must be used in this statement.");
}

void Statement::compileDstPosition(BCodeCommand cmd, Code* code)
{
    RegisterType dst;
    compileDst(cmd, dst, code);

    if (isPositionRegister(dst) || m_dst->type() == ExpressionType::Address)
    {
        return;
    }

    code->error(lineno(), "Only position registers must be used in this statement.");
}

void Statement::compileDstNoPositionSrcPosition(BCodeCommand cmd, Code* code)
{
    RegisterType dst;
    RegisterType src;
    compileDstSrc(cmd, dst, src, code);

    if (isPositionRegister(dst))
    {
        code->error(lineno(), "Position register cannot be used as destination.");
    }

    if (!isPositionRegister(src) && m_src->type() != ExpressionType::Address)
    {
        code->error(lineno(), "Only position registers must be used as source.");
    }
}

}; // namespace Asm
}; // namespace WarAnts
