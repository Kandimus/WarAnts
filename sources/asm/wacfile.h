#pragma once

#include <string>
#include <vector>

namespace WarAnts
{
namespace Asm
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

bool saveWacFile(const std::string& filename, const WacFile& data);
bool loadWacFile(const std::string& filename, WacFile& data);

}; // namespace Asm
}; // namespace WarAnts
