#include "Statement.h"

#include "stringex.h"

#include "defines.h"

#include "code.h"
#include "expression.h"

namespace WarAnts
{
namespace Asm
{

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

    int8_t command = 0;
    int8_t dst = 0;
    int8_t src = 0;
    int16_t dstVal = 0;
    int16_t srcVal = 0;

    switch (m_cmd)
    {
        case AsmCommand::ADD: compileCommon(BCodeCommand::ADD, code); break;
        case AsmCommand::AND: compileNoPosition(BCodeCommand::AND, code); break;
        case AsmCommand::DEC: compileCommonDst(BCodeCommand::DEC, code); break;
        case AsmCommand::DIV: compileCommon(BCodeCommand::DIV, code); break;
        case AsmCommand::INC: compileCommonDst(BCodeCommand::INC, code); break;

        default:
            //SU_BREAKPOINT();
            //return false;
            return true;
    }

    return !code->hasError();
}

static void print2Expr(std::ofstream& file, const std::string& name, Expression* dst, Expression* src)
{
    file << name << " " << dst->toString() << ", " << src->toString();
}

static void print1Expr(std::ofstream& file, const std::string& name, Expression* dst)
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
//            MOD,
        case AsmCommand::MUL:  print2Expr(file, "MUL ", m_dst, m_src); break;
//            NEG,
//            NOT,
        case AsmCommand::OR:   print2Expr(file, "OR  ", m_dst, m_src); break;
        case AsmCommand::SUB:  print2Expr(file, "SUB ", m_dst, m_src); break;
        case AsmCommand::XOR:  print2Expr(file, "XOR ", m_dst, m_src); break;
//            MIN,
//            MAX,

//            BSF,
//            BSR,
//            BT,
//            BTR,
//            BTS,
//            BTC,
//            SHL,
//            SHR,
//            ROL,
//            ROR,

//            EQ,
//            NEQ,
        case AsmCommand::GT:   print2Expr(file, "GT  ", m_dst, m_src); break;
        case AsmCommand::GE:   print2Expr(file, "GE  ", m_dst, m_src); break;
        case AsmCommand::LT:   print2Expr(file, "LT  ", m_dst, m_src); break;
        case AsmCommand::LE:   print2Expr(file, "LE  ", m_dst, m_src); break;
//            TEST,

        case AsmCommand::JMP:  printLabel(file, "JMP ", m_jump); break;
        case AsmCommand::JZ:   printLabel(file, "JZ  ", m_jump); break;
        case AsmCommand::JNZ:  printLabel(file, "JNZ ", m_jump); break;
        case AsmCommand::JO:   printLabel(file, "JO  ", m_jump); break;
//            JNO,
//            JCZ,
//            JCNZ,
        case AsmCommand::LOOP: printLabel(file, "LOOP", m_jump); break;

        case AsmCommand::MOV:  print2Expr(file, "MOV ", m_dst, m_src); break;
//            CALL,
//            LEN,
        case AsmCommand::EXIT: print0Expr(file, "EXIT"); break;

        case AsmCommand::LDTR: print1Expr(file, "LDTR", m_src); break;
        case AsmCommand::LDFD: print1Expr(file, "LDFD", m_src); break;
        case AsmCommand::LDEN: print1Expr(file, "LDEN", m_src); break;
//            LDFR,

        case AsmCommand::CIDL: print1Expr(file, "CIDL", m_src); break;
//            CMOV,
//            CATT,
//            CTKF,
//            CGVF,
        case AsmCommand::CEAT: print1Expr(file, "CEAT", m_src); break;
//            CPS,
//            CPW,

        case AsmCommand::NOP:  print0Expr(file, "NOP"); break;
        default:
            file << "UNDEFINE COMMAND " << (uint32_t)m_cmd << std::endl;
            return;
    }

    if (m_bcode.size())
    {
        file << "\t\t//";

        for (auto item : m_bcode)
        {
            file << std::hex << su::String_format2("%02x ", item) << std::dec;
        }
    }

    file << std::endl;
}

RegisterType Statement::compileExpr(Expression* expr, bool isDst, Code* code)
{
    union
    {
        int16_t s;
        int8_t c[2];
    } val;

    int8_t reg = expr->compile(true, val.s, code);
    
    if (code->hasError())
    {
        return RegisterType::INVALIDE;
    }

    RegisterType clearReg = (RegisterType)(reg & 0x7F);
    m_bcode.push_back(reg);

    if (clearReg == RegisterType::CHAR)
    {
        m_bcode.push_back(val.c[0]);
    }

    if (clearReg == RegisterType::SHORT)
    {
        m_bcode.push_back(val.c[0]);
        m_bcode.push_back(val.c[1]);
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

void Statement::compileCommon(BCodeCommand cmd, Code* code)
{
    RegisterType dst;
    RegisterType src;
    compileDstSrc(cmd, dst, src, code);
}

void Statement::compileCommonDst(BCodeCommand cmd, Code* code)
{
    RegisterType dst;
    compileDst(cmd, dst, code);
}

void Statement::compileCommonSrc(BCodeCommand cmd, Code* code)
{
    RegisterType src;
    compileSrc(cmd, src, code);
}

void Statement::compileNoPosition(BCodeCommand cmd, Code* code)
{
    RegisterType dst;
    RegisterType src;
    compileDstSrc(cmd, dst, src, code);

    if (isPositionRegister(dst))
    {
        code->error(lineno(), "Position register cannot be used in this statement.");
        return;
    }

    if (isPositionRegister(src))
    {
        code->error(lineno(), "Position register cannot be used in this statement.");
        return;
    }
 }

}; // namespace Asm
}; // namespace WarAnts
