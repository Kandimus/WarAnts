
#include <fstream>

#include "log.h"
#include "commandline.h"
#include "stringex.h"

#include "../asm/Compiler.h"

namespace Arg
{
    const su::CommandLineOption LOGDIR = { "logdir", 'l' };
};

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
+---+--------------------------------------------
| n | bcode
+---+--------------------------------------------
*/

int main(int argc, const char **argv)
{
    su::CommandLine cl;

    cl.addOption(Arg::LOGDIR, "./logs/")
      .parse(argc, argv);

    su::Log::instance().setDir(cl.getOption(Arg::LOGDIR));
    su::Log::instance().setLevel(su::Log::Level::Debug);

    uint16_t coreVer = WarAnts::Asm::compileVersion();
    printf("WarAnt compiler ver 1.0, core %04x\n", coreVer);

    printf("Build started...\n");

    for (size_t ii = 0; ii < cl.getCountArgument(); ++ii)
    {
        std::vector<int8_t> data;
        StringArray errors;
        StringArray warnings;
        PragmaMap pragma;
        std::string filename = cl.getArgument((unsigned int)ii);
        auto result = WarAnts::Asm::compileFile(filename, warnings, errors, data, pragma);

        printf("%s\n", filename.c_str());

        if (errors.size())
        {
            for (const auto& err : errors)
            {
                printf("%s\n", err.c_str());
            }
        }
        else
        {
            if (warnings.size())
            {
                for (const auto& wng : warnings)
                {
                    printf("%s\n", wng.c_str());
                }
            }

            std::ofstream file(su::String_rawFilename(filename) + ".wac", std::ios_base::binary);
            
            file.write((const char*)&Magic, sizeof(Magic));

            file.write((const char*)&coreVer, sizeof(coreVer));

            std::string str = pragma[WarAnts::Asm::PragmaType::Class];
            file.write((const char*)str.c_str(), str.size() + 1);

            str = pragma[WarAnts::Asm::PragmaType::Name];
            file.write((const char*)str.c_str(), str.size() + 1);

            str = pragma[WarAnts::Asm::PragmaType::Version];
            file.write((const char*)str.c_str(), str.size() + 1);

            file.write((const char*)data.data(), data.size());

            file.close();
        }
    }

    printf("Build finished...\n");

    return true;
}

