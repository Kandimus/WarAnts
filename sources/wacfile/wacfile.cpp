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

    uint16_t size = (uint16_t)data.size();
    file.write((const char*)&size, sizeof(size));

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


bool loadWacFile(const std::string& filename, std::vector<int8_t>& data, PragmaMap& pragma)
{
    std::ifstream file(filename, std::ios_base::binary);

    data.clear();
    pragma.clear();

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

    uint16_t coreVer = 0;
    file.read((char*)&coreVer, sizeof(coreVer));
    if (coreVer != Asm::Version::Core)
    {
        return false;
    }

    pragma[WarAnts::Asm::PragmaType::Class] = readCString(file);
    pragma[WarAnts::Asm::PragmaType::Name] = readCString(file);
    pragma[WarAnts::Asm::PragmaType::Version] = readCString(file);

    uint16_t size = 0;
    file.read((char*)&size, sizeof(size));

    data.resize(size);
    file.read((char*)data.data(), data.size());

    file.close();

    return true;
}

}; // namespace WarAnts
