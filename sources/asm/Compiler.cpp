
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "code.h"

namespace WarAnts
{
namespace Asm
{

Code* yy_compile(const char* Func, std::string& outError);

bool compileFile(const std::string& filename, std::string& error, std::vector<int8_t>& data)
{
    std::ifstream file(filename);
    std::stringstream buffer;
    std::string text;

    if (!file.is_open())
    {
        return false;
    }

    buffer << file.rdbuf();
    file.close();
    text = buffer.str();

    auto code = yy_compile(text.c_str(), error);

    return true;
}

}; // namespace Asm
}; // namespace WarAnts
