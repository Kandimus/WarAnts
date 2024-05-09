
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "stringex.h"
#include "scopeexit.h"

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
    SU_ON_SCOPE_EXIT( error = code->m_errors; );

    if (error.size())
    {
        return false;
    }

    // Step 1. Uniques function names and uniques label name in one function
    if (!code->checkFunctionsAndNames())
    {
        return false;
    }
    code->print(filename + ".step1.txt");

    // Step 2. Optimize statement tree and experssions

    // Step 3. Move calculation of address in expression to separate statements
    if (!code->extrudeExpression())
    {
        return false;
    }
    code->print(filename + ".step3.txt");

    // Step 4. Optimize statements

    // Step 5. Add EXIT on end of function

    // Step 6. Compile statement to bcode
    if (!code->compile())
    {
        return false;
    }
    code->print(filename + ".step6.txt");

    // Step 7. Calculation jumps and calls
    if (!code->calculationJumpsAndCalls())
    {
        return false;
    }
    code->print(filename + ".step7.txt");

    // Step 8. Forming resulting array

    return true;
}

}; // namespace Asm
}; // namespace WarAnts
