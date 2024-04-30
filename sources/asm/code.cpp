#include <stdarg.h>

#include "code.h"

#include "function.h"
#include "pragma.h"

namespace WarAnts
{
namespace Asm
{

void Code::error(const char* format, ...)
{
    va_list arg;
    char* buff = new char[4096];
    memset(buff, 0, 4096);

    va_start(arg, format);
    vsnprintf_s(buff, 4096, 4096, format, arg);
    va_end(arg);

    std::string result = buff;
    delete[] buff;

    m_errors.push_back("error: " + result);
}

void Code::error(uint32_t lineno, const char* format, ...)
{
    va_list arg;
    char* buff = new char[4096];
    memset(buff, 0, 4096);

    va_start(arg, format);
    vsnprintf_s(buff, 4096, 4096, format, arg);
    va_end(arg);

    std::string result = buff;
    delete[] buff;

    m_errors.push_back(std::to_string(lineno) + ": " + result);
}

bool Code::checkFunctionName()
{
    Function* func = m_function;
    bool foundQueen = false;
    bool foundSolder = false;
    bool foundWorker = false;

    while (func)
    {
        Function* checkFunc = func->next();

        foundQueen |= func->name() == FuncNameQueen;
        foundSolder |= func->name() == FuncNameSolder;
        foundWorker |= func->name() == FuncNameWorker;

        while (checkFunc)
        {
            if (checkFunc->name() == func->name())
            {
                error(checkFunc->lineno(), "Duplicate functions name '%s',", checkFunc->name().c_str());
                error(func->lineno(), "previously declared here");
                return false;
            }
            checkFunc = checkFunc->next();
        }

        func = func->next();
    }

    if (!foundQueen)
    {
        error("Function '%s' not found", FuncNameQueen.c_str());
    }

    if (!foundSolder)
    {
        error("Function '%s' not found", FuncNameSolder.c_str());
    }

    if (!foundWorker)
    {
        error("Function '%s' not found", FuncNameWorker.c_str());
    }

    return foundQueen && foundSolder && foundWorker;
}

bool Code::moveLabelToStatetment()
{
    Function* func = m_function;

    while (func)
    {
        if (!func->moveLabelToStatetment(this))
        {
            return false;
        }

        func = func->next();
    }
}

}; // namespace Asm
}; // namespace WarAnts
