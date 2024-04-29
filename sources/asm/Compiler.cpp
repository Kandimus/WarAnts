
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "stringex.h"

#include "code.h"
#include "function.h"

namespace WarAnts
{
namespace Asm
{

std::shared_ptr<WarAnts::Asm::Code> yy_compile(const char* source);

bool compileFile(const std::string& filename, std::vector<std::string>& error, std::vector<int8_t>& data)
{
    std::ifstream file(filename);
    std::stringstream buffer;
    std::string text;

    error.clear();

    if (!file.is_open())
    {
        error.push_back(su::String_format2("Error: Can not open file: '%s'", filename.c_str()));
        return false;
    }
 
    buffer << file.rdbuf();
    file.close();
    text = buffer.str();

    auto code = yy_compile(text.c_str());
    error = code->m_errors;

    if (error.size())
    {
        return false;
    }

    // Step 1. Uniques function names

    // Step 1. removing labels as single statetment.
    //auto func = code->m_function;
    //while (func)
    //{
    //    auto stat = func->m_stat;
    //}
    return true;
}

}; // namespace Asm
}; // namespace WarAnts
