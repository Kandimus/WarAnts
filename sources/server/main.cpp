
#include "Battle.h"
#include "log.h"
#include "commandline.h"

namespace Arg
{
    const su::CommandLineOption CONFIG = { "config", 'c' };
    const su::CommandLineOption LOGDIR = { "logdir", 'l' };
    const su::CommandLineOption MAP = { "map", 'm' };
    const su::CommandLineOption SEED = { "seed", 's' };
};

int main(int argc, const char **argv)
{
    su::CommandLine cl;

    cl.addOption(Arg::CONFIG, "default.json")
      .addOption(Arg::LOGDIR, "./logs/")
      .addOption(Arg::MAP, "")
      .addOption(Arg::SEED, "")
      .parse(argc, argv);

    su::Log::instance().setDir(cl.getOption(Arg::LOGDIR));
    su::Log::instance().setLevel(su::Log::Level::Debug);

    std::string configname = cl.getOption(Arg::CONFIG);
    if (configname.empty())
    {
        printf("You need to specify the configuration file!");
        return 1;
    }

    std::vector<std::string> plr_list;

    for (int ii = 0; ii < cl.getCountArgument(); ++ii)
    {
        plr_list.push_back(cl.getArgument(ii));
    }

    uint32_t seed = static_cast<uint32_t>(std::time(nullptr));
    if (cl.getOption(Arg::SEED).size())
    {
        char* errChar = nullptr;
        seed = std::strtoul(cl.getOption(Arg::SEED).c_str(), &errChar, 10);
    }

    WarAnts::Battle battle(configname, cl.getOption(Arg::MAP), plr_list, seed);

    return battle.run();
}

