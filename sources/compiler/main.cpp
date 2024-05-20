
#include <fstream>

#include "log.h"
#include "commandline.h"
#include "stringex.h"

#include "Compiler.h"
#include "wacfile.h"

namespace Arg
{
    const su::CommandLineOption LOGDIR = { "logdir", 'l' };
};

int main(int argc, const char **argv)
{
    su::CommandLine cl;

    cl.addOption(Arg::LOGDIR, "./logs/")
      .parse(argc, argv);

    su::Log::instance().setDir(cl.getOption(Arg::LOGDIR));
    su::Log::instance().setLevel(su::Log::Level::Debug);

    uint16_t coreVer = WarAnts::Asm::compileVersion();
    printf("WarAnt compiler ver 1.0, core %04x\n", coreVer);

    printf("----- Build started... -----\n");

    for (size_t ii = 0; ii < cl.getCountArgument(); ++ii)
    {
        WarAnts::Asm::WacFile wac;
        StringArray errors;
        StringArray warnings;
        std::string filename = cl.getArgument((unsigned int)ii);
        auto result = WarAnts::Asm::compileFile(filename, warnings, errors, wac);

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

            std::string wacFilename = su::String_rawFilename(filename) + ".wac";
            if (!WarAnts::Asm::saveWacFile(wacFilename, wac))
            {
                printf("Error: Fault to save '%s' file.\n", wacFilename.c_str());
            }
        }
    }

    printf("===== Build finished... =====\n");

    return true;
}

