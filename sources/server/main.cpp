
#include "Battle.h"
#include "log.h"
#include "commandline.h"

namespace Arg
{
    const su::CommandLineOption CONFIG = { "config", 'c' };
    const su::CommandLineOption LOGDIR = { "logdir", 'l' };
};

int main(int argc, const char **argv)
{
    su::CommandLine cl;

    cl.addOption(Arg::CONFIG, "default.json")
      .addOption(Arg::LOGDIR, "./logs/")
      .parse(argc, argv);

    su::Log::instance().setDir(cl.getOption(Arg::LOGDIR));
    su::Log::instance().setLevel(su::Log::Level::Debug);

    std::string configname = cl.getOption(Arg::CONFIG);
    if (configname.empty())
    {
        LOGE("Do not selected configuration file!");
        return 1;
    }

    std::vector<std::string> plr_list;

    for (int ii = 0; ii < cl.getCountArgument(); ++ii)
    {
        plr_list.push_back(cl.getArgument(ii));
    }

    WarAnts::Battle battle("./config/" + configname, plr_list);

    return battle.run();
}

