#include "wacfile.h"

#include <fstream>
#include <sstream>

#include "stringex.h"

#include "asm_defines.h"
#include "wacfile.h"

const uint32_t Magic = 0x43414157; // WAAC

/*
+------------------------------------------------
| WAC file format
+---+--------------------------------------------
| 4 | WAAC magic number
| 2 | Version of core
| n | c-style string of ant class
| n | c-style string of player copyright
| n | c-style string of player version
| 2 | Queen function offset
| 2 | Solder function offset
| 2 | Worker function offset
| 2 | size of code
| n | n bytes of code
+---+--------------------------------------------
*/

namespace WarAnts
{
namespace Asm
{

bool saveWacFile(const std::string& filename, const WacFile& wac)
{
    std::ofstream file(filename, std::ios_base::binary);
    if (!file.is_open())
    {
        return false;
    }

    uint16_t size = static_cast<uint16_t>(wac.bcode.size());

    file.write((const char*)&Magic, sizeof(Magic));
    file.write((const char*)&wac.coreVersion, sizeof(wac.coreVersion));
    file.write(wac.teamClass.c_str(), wac.teamClass.size() + 1);
    file.write(wac.teamName.c_str(), wac.teamName.size() + 1);
    file.write(wac.teamVersion.c_str(), wac.teamVersion.size() + 1);
    file.write((const char*)&wac.funcQueen, sizeof(wac.funcQueen));
    file.write((const char*)&wac.funcSolder, sizeof(wac.funcSolder));
    file.write((const char*)&wac.funcWorker, sizeof(wac.funcWorker));
    file.write((const char*)&size, sizeof(size));
    file.write((const char*)wac.bcode.data(), wac.bcode.size());
    file.close();

    return true;
}

static std::string readCString(std::ifstream& ifs)
{
    char ch = -1;
    std::string out = "";
    while (ch)
    {
        ifs.read(&ch, 1);
        if (ch)
        {
            out += ch;
        }
    }
    return out;
}


bool loadWacFile(const std::string& filename, WacFile& data)
{
    std::ifstream file(filename, std::ios_base::binary);

    data.coreVersion = 0xffff;
    data.funcQueen = 0xffff;
    data.funcSolder = 0xffff;
    data.funcWorker = 0xffff;
    data.bcode.clear();
    data.teamClass = "";
    data.teamName = "";
    data.teamVersion = "";

    if (!file.is_open())
    {
        return false;
    }

    uint32_t magic = 0;
    file.read((char*)&magic, sizeof(magic));
    if (magic != Magic)
    {
        return false;
    }

    file.read((char*)&data.coreVersion, sizeof(data.coreVersion));
    if (data.coreVersion != Version::Core)
    {
        return false;
    }

    data.teamClass = readCString(file);
    data.teamName = readCString(file);
    data.teamVersion = readCString(file);

    file.read((char*)&data.funcQueen, sizeof(data.funcQueen));
    file.read((char*)&data.funcSolder, sizeof(data.funcSolder));
    file.read((char*)&data.funcWorker, sizeof(data.funcWorker));

    uint16_t size = 0;
    file.read((char*)&size, sizeof(size));

    data.bcode.resize(size);
    file.read((char*)data.bcode.data(), data.bcode.size());

    file.close();

    return true;
}

}; // namespace Asm
}; // namespace WarAnts
