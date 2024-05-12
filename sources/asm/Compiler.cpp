#include "Compiler.h"

#include <fstream>
#include <sstream>

#include "stringex.h"
#include "scopeexit.h"

#include "code.h"
#include "function.h"

namespace WarAnts
{
namespace Asm
{

const uint16_t Code::CoreVersion = 0x0100;

std::shared_ptr<WarAnts::Asm::Code> yy_compile(const char* source);

uint16_t compileVersion()
{
    return Code::CoreVersion;
}

bool compileFile(const std::string& filename,
    StringArray& warnings, StringArray& errors,
    std::vector<int8_t>& data, PragmaMap& pragma)
{
    std::ifstream file(filename);
    std::stringstream buffer;
    std::string text;

    warnings.clear();
    errors.clear();
    pragma.clear();

    if (!file.is_open())
    {
        errors.push_back(su::String_format2("Error: Can not open file: '%s'", filename.c_str()));
        return false;
    }

    buffer << file.rdbuf();
    file.close();
    text = buffer.str();
    text += "\n";

    auto code = yy_compile(text.c_str());
    SU_ON_SCOPE_EXIT( errors.insert(errors.end(), code->m_errors.begin(), code->m_errors.end()); );

    if (errors.size())
    {
        return false;
    }

    // Step 0. Check the version of core and class of ants
    std::string userCore = code->getPragma(PragmaType::Core);
    std::string strCore = su::String_format2("%04x", code->CoreVersion);
    if (userCore.size() && strCore != userCore)
    {
        errors.push_back(su::String_format2("Error: Version of core not equal %s", strCore.c_str()));
        return false;
    }

    std::string antClass = code->getPragma(PragmaType::Class);
    if (antClass.empty())
    {
        errors.push_back("Error: Not defined the class of ants.");
        return false;
    }

    // Step 1. Uniques function names and uniques label name in one function
    if (!code->checkFunctionsAndNames())
    {
        return false;
    }
    code->print(filename + ".step1.txt");

    // Step 2. Optimize statement tree and experssions
    //         Remove unused functions
    if (!code->removeUnusedFunctions())
    {
        return false;
    }

    // Step 3. Move calculation of address in expression to separate statements
    if (!code->extrudeExpression())
    {
        return false;
    }
    code->print(filename + ".step3.txt");

    // Step 4. Optimize statements

    // Step 5. Add EXIT on end of function
    if (!code->checkExitStatement())
    {
        return false;
    }
    code->print(filename + ".step5.txt");

    // Step 6. Compile statement to bcode
    if (!code->compile())
    {
        return false;
    }
    code->print(filename + ".step6.txt");

    // Step 7. Optimize BCode statements
    //         Value statements
    if (!code->optimizeValueStatement())
    {
        return false;
    }
    code->print(filename + ".step7.txt");

    // Step 8. Calculation jumps and calls
    //         Remove "fake" jumps (fake jump is a jump to the next statement)
    if (!code->calculationJumpsAndCalls())
    {
        return false;
    }
    code->print(filename + ".step8.txt");

    // Step 9. Forming resulting array
    if (!code->save(data))
    {
        return false;
    }
    code->printData(su::String_rawFilename(filename) + ".out");

    pragma[PragmaType::Class] = code->getPragma(PragmaType::Class);
    pragma[PragmaType::Core] = code->getPragma(PragmaType::Core);
    pragma[PragmaType::Name] = code->getPragma(PragmaType::Name);
    pragma[PragmaType::Version] = code->getPragma(PragmaType::Version);

    warnings = code->m_warnings;

    return true;
}

}; // namespace Asm
}; // namespace WarAnts
