#pragma once

namespace WarAnts
{

namespace Interrupt
{
enum Type : uint16_t
{
    CommandAborted = 0x0001,     // 
    CommandCompleted = 0x0002,   // 
    WasAttacked = 0x0004,        // set in Ant::damage
    CloseEnemy = 0x0008,         // set in Battle::processingInterrupt
    FarEnemy = 0x0010,           // set in Battle::processingInterrupt
    CloseFood = 0x0020,          // set in Battle::processingInterrupt
    FarFood = 0x0040,            // set in Battle::processingInterrupt
    LowSatiety = 0x0080,         // set in Ant::endTurn
    MiddleSatiety = 0x0100,      // set in Ant::endTurn
    LowHealth = 0x0200,          // set in Ant::endTurn
    MiddleHealth = 0x0400,       // set in Ant::endTurn
    QueenUnderAttack = 0x0800,   // set in Battle::processingInterrupt
    ReceivedMessage = 0x1000,    //TODO Not implemented
    Reserved_2000,
    Reserved_4000,
    Timer = 0x8000,              //TODO Not implemented
};

} // namespace Interrupt

class AntDefinition
{
public:
    enum Type
    {
        Queen = 0,
        Solder,
        Worker,

        __MAX,
    };

    enum Status
    {
        Life = 0,
        Dead,
    };

    enum DeathReason
    {
        StillAlife = 0,
        KilledByAnt = 1,
        Hunger,
        PlayerLoose,
    };
};

} // namespace WarAnts
