#include <chrono>
#include <fstream>
#include <stdarg.h>

#include "stream_std.h"

#include "code.h"

#include "function.h"
#include "pragma.h"
#include "wacfile.h"

namespace WarAnts
{
namespace Asm
{

const uint16_t Code::CoreVersion = Version::Core;

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

    m_errors.push_back(std::to_string(lineno) + ": Error:" + result);
}

void Code::warning(uint32_t lineno, const char* format, ...)
{
    va_list arg;
    char* buff = new char[4096];
    memset(buff, 0, 4096);

    va_start(arg, format);
    vsnprintf_s(buff, 4096, 4096, format, arg);
    va_end(arg);

    std::string result = buff;
    delete[] buff;

    m_warnings.push_back(std::to_string(lineno) + ": Warning:" + result);
}

uint16_t Code::updateOffset(uint16_t addOffset)
{
    int16_t out = m_offset;
    m_offset += addOffset;
    return out;
}

bool Code::checkFunctionsAndNames()
{
    Function* func = m_function;
    
    m_funcQueen = nullptr;
    m_funcSolder = nullptr;
    m_funcWorker = nullptr;

    while (func)
    {
        Function* checkFunc = func->next();

        if (func->name() == FuncNameQueen)
        {
            m_funcQueen = func;
            m_funcQueen->setUsed(true);
        }
        else if (func->name() == FuncNameSolder)
        {
            m_funcSolder = func;
            m_funcSolder->setUsed(true);
        }
        else if (func->name() == FuncNameWorker)
        {
            m_funcWorker = func;
            m_funcWorker->setUsed(true);
        }

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

        if (!func->checkLabelNames(this))
        {
            return false;
        }

        func = func->next();
    }

    if (!m_funcQueen)
    {
        error("Function '%s' not found", FuncNameQueen.c_str());
    }

    if (!m_funcQueen)
    {
        error("Function '%s' not found", FuncNameSolder.c_str());
    }

    if (!m_funcQueen)
    {
        error("Function '%s' not found", FuncNameWorker.c_str());
    }

    return !!m_funcQueen && !!m_funcSolder && !!m_funcWorker;
}

bool Code::removeUnusedFunctions()
{
    Function* func = m_function;
    Function* prev = nullptr;

    while (func)
    {
        if (!func->used())
        {
            warning(func->lineno(), "The function '%s' has been removed because it unused.", func->name().c_str());

            if (prev)
            {
                prev->m_next = func->next();
            }
            else
            {
                m_function = func->next();
            }
            // функцию удалит общий сборщик мусора
        }

        prev = func;
        func = func->next() ;
    }

    return true;
}

bool Code::extrudeExpression()
{
    Function* func = m_function;

    while (func)
    {
        if (!func->extrudeExpression(this))
        {
            return false;
        }

        func = func->next();
    }

    return true;
}

Function* Code::getFunction(const std::string& name) const
{
    Function* func = m_function;

    while (func)
    {
        if (func->name() == name)
        {
            return func;
        }

        func = func->next();
    }

    return nullptr;
}

std::string Code::getPragma(PragmaType type) const
{
    auto pragma = m_pragma;

    while (pragma)
    {
        if (pragma->type() == type)
        {
            return pragma->value();
        }

        pragma = pragma->next();
    }

    return "";
}

bool Code::checkExitStatement()
{
    auto func = m_function;

    while (func)
    {
        if (!func->checkExitStatement(this))
        {
            return false;
        }
        func = func->next();
    }

    return true;
}

bool Code::compile()
{
    auto func = m_function;

    while (func)
    {
        if (!func->compile(this))
        {
            return false;
        }
        func = func->next();
    }

    return true;
}

bool Code::optimizeValueStatement()
{
    auto func = m_function;

    while (func)
    {
        if (!func->optimizeValueStatement(this))
        {
            return false;
        }
        func = func->next();
    }

    return true;
}

bool Code::calculationJumpsAndCalls()
{
    bool recalc = true;

    while (recalc)
    {
        if (!assignOffsets())
        {
            return false;
        }

        if (!resolveLabels(recalc))
        {
            return false;
        }
    }

    return true;
}

bool Code::assignOffsets()
{
    auto func = m_function;

    m_offset = 0;

    while (func)
    {
        if (!func->assignOffsets(this))
        {
            return false;
        }

        func = func->next();
    }

    return true;
}

bool Code::resolveLabels(bool& recalc)
{
    auto func = m_function;

    recalc = false;

    while (func)
    {
        if (!func->resolveLabels(recalc, this))
        {
            return false;
        }

        func = func->next();
    }

    return true;
}

bool Code::save(WacFile& wac)
{
    auto func = m_function;
    while (func)
    {
        if (!func->save(this))
        {
            return false;
        }

        func = func->next();
    }

    wac.funcQueen = m_funcQueen->offset();
    wac.funcSolder = m_funcSolder->offset();
    wac.funcWorker = m_funcWorker->offset();

    wac.teamClass = getPragma(PragmaType::Class);
    wac.coreVersion = CoreVersion;
    wac.teamName = getPragma(PragmaType::Name);
    wac.teamVersion = getPragma(PragmaType::Version);

    wac.bcode = m_data;

    return true;
}

void Code::print(const std::string& filename)
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        fprintf(stderr, "Critical error: Cannot open file '%s'\n", filename.c_str());
        return;
    }

    file << "; pragma" << std::endl;
    auto pragma = m_pragma;
    while (pragma)
    {
        file << (size_t)pragma->type() << " = '" << pragma->value() << "'" << std::endl;
        pragma = pragma->next();
    }
    file << std::endl;

    auto func = m_function;
    while (func)
    {
        func->print(file);
        func = func->next();
    }
    file.close();
}

void Code::printData(const std::string& filename)
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        fprintf(stderr, "Critical error: Cannot open file '%s'\n", filename.c_str());
        return;
    }

    std::time_t curTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char buff[1024] = {0};
    ctime_s(buff, 1024, &curTime);
    std::string curStrTime = buff;
    curStrTime = curStrTime.substr(0, curStrTime.size() - 1);

    file << "info:" << std::endl;
    file << "    core    " << getPragma(PragmaType::Core) << std::endl;
    file << "    name    " << getPragma(PragmaType::Name) << std::endl;
    file << "    class   " << getPragma(PragmaType::Class) << std::endl;
    file << "    version " << getPragma(PragmaType::Version) << std::endl;
    file << "    data    " << curStrTime << std::endl;
    file << "    size    " << m_data.size() << " bytes" << std::endl;
    file << std::endl;

    file << "offsets:" << std::endl;
    file << "    .queen  " << su::String_format2("%04x", m_funcQueen->offset()) << std::endl;
    file << "    .solder " << su::String_format2("%04x", m_funcSolder->offset()) << std::endl;
    file << "    .worker " << su::String_format2("%04x", m_funcWorker->offset()) << std::endl;
    file << std::endl;

    file << "       00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F" << std::endl;
    file << "     +------------------------------------------------" << std::endl;

    size_t count = 0;
    for (auto val8 : m_data)
    {
        if ((count & 0x0f) == 0)
        {
            file << su::String_format2("%04x |", count & 0xfff0);
        }

        int32_t val32 = val8;
        val32 &= 0xff;
        file << su::String_format2(" %02x", val32);

        if ((count & 0x0f) == 0x0f)
        {
            file << std::endl;
        }
        ++count;
    }
    file << std::endl;
    file.close();
}

}; // namespace Asm
}; // namespace WarAnts
