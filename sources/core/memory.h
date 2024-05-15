#pragma once

#include <stdint.h>

namespace WarAnts
{

enum Memory
{
    Iteration = 0x00,
    SatietyPercent = 0x02,
    HealthPercent = 0x03,
    Cargo = 0x04,
    CountOfAllies = 0x05,
    CountOfEnemy = 0x06,
    CountOfFood = 0x07,
    CountOfWorkers = 0x08,
    CountOfSolders = 0x09,
    InteraptReason = 0x0a,
    LastCommand_Id = 0x0b,
    LastCommand_X = 0x0c,
    LastCommand_Y = 0x0d,

    ReadOnly = 0x1f,
    UserData = 0x30,
};

};
