#include "function.h"
#include "code.h"
#include "Statement.h"

namespace WarAnts
{
namespace Asm
{

bool Function::checkLabelNames(Code* code)
{
    auto stat = m_stat;

    while (stat)
    {
        if (stat->type() == StatementType::Label)
        {
            auto checkStat = stat->next();

            while (checkStat)
            {
                if (checkStat->type() == StatementType::Label)
                {
                    if (checkStat->label() == stat->label())
                    {
                        code->error(checkStat->lineno(), "Duplicate label name '%s',", checkStat->label().c_str());
                        code->error(stat->lineno(), "previously declared here");
                        return false;
                    }
                }

                checkStat = checkStat->next();
            }

        }

        stat = stat->next();
    }
    return true;
}

bool Function::extrudeExpression(Code* code)
{
    Statement* stat = m_stat;
    Statement* prev = nullptr;

    while (stat)
    {
        auto newStat = stat->extrudeExpression(code);

        if (code->hasError())
        {
            return false;
        }

        if (newStat)
        {
            if (prev)
            {
                prev->m_next = newStat;
                newStat->add(stat);
            }
            else
            {
                m_stat = newStat;
                m_stat->add(stat);
            }
        }

        prev = stat;
        stat = stat->next();
    }

    return true;
}

bool Function::compile(Code* code)
{
    Statement* stat = m_stat;

    while (stat)
    {
        if (!stat->compile(code))
        {
            return false;
        }

        stat = stat->next();
    }

    return true;
}

void Function::print(std::ofstream& file)
{
    file << "." << m_name << std::endl;

    Statement* stat = m_stat;

    while (stat)
    {
        stat->print(file);
        stat = stat->next();
    }

    file << std::endl;
}

}; // namespace Asm
}; // namespace WarAnts
