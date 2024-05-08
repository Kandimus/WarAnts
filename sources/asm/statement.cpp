#include "Statement.h"

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

    int16_t command = 0;
    int8_t dst = 0;
    int8_t src = 0;

    switch (m_cmd)
    {
        case AsmCommand::AND:
            //code->addCode();
            command = ((int8_t)AsmCommand::AND) & 0x3f;
            //dst = m_dst->compile(true, code);
            //src = m_src->compile(false, code);
            break;

        default:
            SU_BREAKPOINT();
            return false;
    }

    return true;
}

static void print2Expr(std::ofstream& file, const std::string& name, Expression* dst, Expression* src)
{
    file << name << " " << dst->toString() << ", " << src->toString() << std::endl;
}

static void print1Expr(std::ofstream& file, const std::string& name, Expression* dst)
{
    file << name << " " << dst->toString() << std::endl;
}

static void print0Expr(std::ofstream& file, const std::string& name)
{
    file << name << std::endl;
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
//            INC,
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
//            GT,
//            GE,
//            LT,
        case AsmCommand::LE:   print2Expr(file, "LE  ", m_dst, m_src); break;
//            TEST,

//            JMP,
//            JZ,
//            JNZ,
//            JO,
//            JNO,
//            JCZ,
//            JCNZ,
        case AsmCommand::LOOP: print0Expr(file, "LOOP"); break;

        case AsmCommand::MOV:  print2Expr(file, "MOV ", m_dst, m_src); break;
//            CALL,
//            LEN,
        case AsmCommand::EXIT: print0Expr(file, "EXIT"); break;

        case AsmCommand::LDTR: print1Expr(file, "LDTR", m_src); break;
        case AsmCommand::LDFD: print1Expr(file, "LDFD", m_src); break;
        case AsmCommand::LDEN: print1Expr(file, "LDEN", m_src); break;
//            LDFR,

//            CIDL,
//            CMOV,
//            CATT,
//            CTKF,
//            CGVF,
        case AsmCommand::CEAT: print1Expr(file, "CEAT", m_src); break;
//            CPS,
//            CPW,

        case AsmCommand::NOP:  print0Expr(file, "NOP"); break;
        default: file << "UNDEFINE COMMAND " << (uint32_t)m_cmd << std::endl; break;
    }
}

}; // namespace Asm
}; // namespace WarAnts
