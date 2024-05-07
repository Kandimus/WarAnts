#include "Statement.h"

#include "defines.h"

#include "code.h"
#include "expression.h"

namespace WarAnts
{
namespace Asm
{

/*

| 0 ... 5 | 6 ... 10 | 11 ... 15 |
 ----+---- ----+----- -----+-----
     |         |           |
     |         |           +--- source
     |         +--------------- destination
     +------------------------- command code



*/
Statement* Statement::extrudeExpression(Code* code)
{
    Statement* out = nullptr;
    Statement* statDst = nullptr;
    Statement* statSrc = nullptr;

    if (m_dst)
    {
        statDst = m_dst->extrudeExpression(true, code);
    }

    if (m_src)
    {
        statSrc = m_src->extrudeExpression(false, code);
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
        case AsmCommand::ADD: file << "ADD  " << m_dst->toString() << ", " << m_src->toString() << std::endl; break;
        case AsmCommand::AND: file << "AND  " << m_dst->toString() << ", " << m_src->toString() << std::endl; break;
//            DEC,
//            DIV,
//            INC,
//            MOD,
        case AsmCommand::MUL: file << "MUL  " << m_dst->toString() << ", " << m_src->toString() << std::endl; break;
//            NEG,
//            NOT,
//            OR,
//            SUB,
//            XOR,
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
//            LE,
//            TEST,

//            JMP,
//            JZ,
//            JNZ,
//            JO,
//            JNO,
//            JCZ,
//            JCNZ,
//            LOOP,

        case AsmCommand::MOV: file << "MOV  " << m_dst->toString() << ", " << m_src->toString() << std::endl; break;
//            CALL,
//            LEN,
//            EXIT,

//            LDTR,
//            LDFD,
//            LDEN,
//            LDFR,

//            CIDL,
//            CMOV,
//            CATT,
//            CTKF,
//            CGVF,
//            CEAT,
//            CPS,
//            CPW,

        case AsmCommand::NOP: file << "NOP" << std::endl; break;
        default: file << "UNDEFINE COMMAND " << (uint32_t)m_cmd << std::endl; break;
    }
}

}; // namespace Asm
}; // namespace WarAnts
