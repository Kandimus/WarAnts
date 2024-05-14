#pragma once

#include <unordered_map>
#include <vector>

#include "asm_defines.h"

using PragmaMap = std::unordered_map<WarAnts::Asm::PragmaType, std::string>;

namespace WarAnts
{

struct WacFile
{
    uint16_t coreVersion = 0;
    uint16_t funcQueen = 0xffff;
    uint16_t funcSolder = 0xffff;
    uint16_t funcWorker = 0xffff;
    std::vector<int8_t> bcode;

    std::string teamName;
    std::string teamClass;
    std::string teamVersion;
};


bool saveWacFile(const std::string& filename, const std::vector<int8_t>& data, PragmaMap& pragma);
bool loadWacFile(const std::string& filename, WacFile& data);

}; // namespace WarAnts
