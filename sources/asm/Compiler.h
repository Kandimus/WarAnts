#pragma once

//#include <set>
#include <string>
//#include <unordered_map>
#include <vector>

#include "wacfile.h"

using StringArray = std::vector<std::string>;
//using PragmaMap = std::unordered_map<WarAnts::Asm::PragmaType, std::string>;

namespace WarAnts
{
namespace Asm
{

uint16_t compileVersion();

bool compileFile(
    const std::string& filename,
    StringArray& warnings,
    StringArray& errors,
    WacFile& wac);

}; // namespace Asm
}; // namespace WarAnts
