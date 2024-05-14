#include "wacfile.h"

#include <fstream>
#include <sstream>

#include "stringex.h"

#include "asm_defines.h"

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
| 2 | size of bcode
+---+--------------------------------------------
| n | bcode
+---+--------------------------------------------
*/

namespace WarAnts
{

bool saveWacFile(const std::string& filename, const std::vector<int8_t>& data, PragmaMap& pragma)
{
    std::ofstream file(filename, std::ios_base::binary);
    if (!file.is_open())
    {
        return false;
    }

    file.write((const char*)&Magic, sizeof(Magic));

    uint16_t coreVer = Asm::Version::Core;
    file.write((const char*)&coreVer, sizeof(coreVer));

    std::string str = pragma[WarAnts::Asm::PragmaType::Class];
    file.write((const char*)str.c_str(), str.size() + 1);

    str = pragma[WarAnts::Asm::PragmaType::Name];
    file.write((const char*)str.c_str(), str.size() + 1);

    str = pragma[WarAnts::Asm::PragmaType::Version];
    file.write((const char*)str.c_str(), str.size() + 1);

    file.write((const char*)data.data(), data.size());

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
    if (data.coreVersion != Asm::Version::Core)
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

}; // namespace WarAnts
