
#include <fstream>
#include <sstream>
#include <string>

#include "stringex.h"

#include "code.h"
#include "function.h"

namespace WarAnts
{
namespace Asm
{

Code* yy_compile(const char* Func, std::string& outError);

bool compileFile(const std::string& filename, std::string& strError)
{
    std::ifstream file(filename);
    std::stringstream buffer;
    std::string text;

    if (!file.is_open())
    {
        strError = su::String_format2("Error: Can not open file: '%s'", filename.c_str());
        return false;
    }
 
    strError.clear();
    buffer << file.rdbuf();
    file.close();
    text = buffer.str();

    auto code = yy_compile(text.c_str(), strError);

    if (strError.size())
    {
        delete code;
        return false;
    }

    // Step 1. Uniques function names

    // Step 1. removing labels as single statetment.
    auto func = code->m_function;
    while (func)
    {
        auto stat = func->m_stat;
    }
}

}; // namespace Asm
}; // namespace WarAnts
