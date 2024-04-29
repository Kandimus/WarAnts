
#include "log.h"
#include "commandline.h"

#include "../asm/Compiler.h"

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

    printf("Build started...\n");

    for (size_t ii = 0; ii < cl.getCountArgument(); ++ii)
    {
        std::vector<int8_t> data;
        std::string error;
        std::string filename = cl.getArgument(ii);
        auto result = WarAnts::Asm::compileFile(filename, error, data);

        printf("%s\n", filename.c_str());

        if (error.size())
        {
            printf("%s\n", error.c_str());
        }
    }

    return true;
}

