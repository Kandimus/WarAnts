#pragma once

#include <stdint.h>

namespace WarAnts
{

enum Memory
{
    // Readonly data
    Iteration = 0x00,
    SatietyPercent = 0x02,
    HealthPercent = 0x03,
    Cargo = 0x04,
    CountOfAllies = 0x05,
    CountOfEnemies = 0x06,
    CountOfFoods = 0x07,
    CountOfReceivedData = 0x08,
    CountOfWorkers = 0x09,
    CountOfSolders = 0x0a,
    InterruptReason = 0x0b,
    CommandId = 0x0c,
    CommandX = 0x0d,
    CommandY = 0x0e,
    CommandValue = 0x0f,
    ReceivedData = 0x10,
    ReceivedData0 = 0x10,
    ReceivedData1 = 0x11,
    ReceivedData2 = 0x12,
    ReceivedData4 = 0x13,
    Enemy = 0x14,
    EnemyType = 0x14,
    EnemyCoordX = 0x15,
    EnemyCoordY = 0x16,
        Reserved23 = 0x17,
    Ally = 0x18,
    AllyType = 0x18,
    AllyCoordX = 0x19,
    AllyCoordY = 0x1a,
        Reserved27 = 0x1b,
    Food = 0x1c,
    FoodCoordX = 0x1c,
    FoodCoordY = 0x1d,
        Reserved30 = 0x1e,
        Reserved31 = 0x1f,

    // writebly data
    TransmitingData = 0x20,
    TransmitingData0 = 0x20,
    TransmitingData1 = 0x21,
    TransmitingData2 = 0x22,
    TransmitingData3 = 0x23,
    InterruptFlags = 0x24,
        Reserved37 = 0x25,
        Reserved38 = 0x26,
        Reserved39 = 0x27,
        Reserved40 = 0x28,
        Reserved41 = 0x29,
        Reserved42 = 0x2a,
        Reserved43 = 0x2b,
        Reserved44 = 0x2c,
        Reserved45 = 0x2d,
        Reserved46 = 0x2e,
        Reserved47 = 0x2f,

    ReadOnly = 0x1f,
    UserData = 0x30,
};

};
