
#include <fstream>
#include <sstream>
#include <string>

#include "code.h"

namespace WarAnts
{
namespace Asm
{

Code* yy_compile(const char* Func, std::string& outError);

void compileFile(const std::string& filename)
{
    std::ifstream file(filename);
    std::stringstream buffer;
    std::string text;

    if (!file.is_open())
    {
        return;
    }

    buffer << file.rdbuf();
    file.close();
    text = buffer.str();

    std::string strError = "";
    auto code = yy_compile(text.c_str(), strError);
}

}; // namespace Asm
}; // namespace WarAnts
