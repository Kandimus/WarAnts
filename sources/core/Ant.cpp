#include "Ant.h"

#include "constants.h"
#include "jsonhelper.h"
#include "memory.h"
#include "player.h"

namespace WarAnts
{

std::string AntTypeToString(Ant::Type type)
{
    switch (type)
    {
        case Ant::Type::Queen: return "queen";
        case Ant::Type::Solder: return "solder";
        case Ant::Type::Worker: return "worker";
        default: return "?";
    }
}

Ant::Ant(const nlohmann::json& json, Type type)
{
    m_type = type;
    m_maxHealth = JsonHelper::getValue1<int16_t>(json, "health", m_maxHealth, 1, 0x7fff);
    m_attack = JsonHelper::getValue1<int16_t>(json, "attack", m_attack, 1, 0x7fff);
    m_visibility = JsonHelper::getValue1<int16_t>(json, "visibility", m_visibility, 1, 0x7fff);
    m_maxSatiety = JsonHelper::getValue1<int16_t>(json, "satiety", m_maxSatiety, 1, 0x7fff);
    m_redicedSatiety = JsonHelper::getValue1<int16_t>(json, "RedicedSatiety", m_redicedSatiety, 1, 0x7fff);
    m_foodPerTurn = JsonHelper::getValue1<int16_t>(json, "FoodPerTurn", m_foodPerTurn, 0, 0x7fff);
    m_hungerDamage = JsonHelper::getValue1<int16_t>(json, "HungerDamage", m_hungerDamage, 1, 0x7fff);
    m_maxCargo = JsonHelper::getValue1<int16_t>(json, "cargo", m_maxCargo, 0, 0x7fff);
    m_sizeOfMemory = JsonHelper::getValue1<int16_t>(json, "memory", m_sizeOfMemory, 0, 256);
    m_turnToSolder = JsonHelper::getValue1<int16_t>(json, "solder", m_turnToSolder, 0, 0x7fff);
    m_turnToWorker = JsonHelper::getValue1<int16_t>(json, "worker", m_turnToWorker, 0, 0x7fff);

    m_memory.clear();
    m_memory.resize(Memory::UserData + m_sizeOfMemory);

    reset();
}

std::string Ant::typeToString() const
{
    return AntTypeToString(type());
}

void Ant::reset()
{
    m_satiety = m_maxSatiety;
    m_health = m_maxHealth;
    m_cargo = 0;
}

bool Ant::damage(Ant& ant)
{
    auto damage = ant.attack();

    m_player->addReceivedDamage(type(), damage);
    ant.player()->addDealtDamage(ant.type(), damage);

    m_health -= damage;
    m_isUnderAttack = true;

    if (checkDie())
    {
        //TODO m_player->dieReason(ANT);
        ant.killed(ant.type());
        return false;
    }

    setInterruptReason(Interrupt::WasAttacked, true);
    return true; // The ant is alive
}

void Ant::kill(DeathReason reason)
{
    m_status = Status::Dead;
    m_deathReason = reason;
}

void Ant::killed(Type type)
{
    if (type >= Ant::Type::__MAX)
    {
        return;
    }

    ++m_killed[type];
    m_player->addKilled(type);
}

int16_t Ant::eat(int16_t food)
{
    food = food + m_satiety > m_maxSatiety ? m_maxSatiety - m_satiety : food;
    m_satiety += food;
    return food;
}

int16_t Ant::eatFromCargo()
{
    int16_t food = std::min(std::min(m_cargo, m_foodPerTurn), missingSatiety());

    m_cargo -= food;
    m_satiety += food;

    return food;
}

bool Ant::beginTurn()
{
    ++m_lifeCount;
    m_isUnderAttack = false;

    return true;
}

bool Ant::postVM()
{
    // Clear IR
    m_interruptReason = 0;
    // Copy IF form memory to variable
    m_interruptFlags = m_memory[Memory::InterruptFlags] | Interrupt::CommandAborted | Interrupt::CommandCompleted;

    return true;
}

bool Ant::endTurn()
{
    m_satiety -= m_redicedSatiety;

    if (m_satiety < 0)
    {
        m_satiety = 0;
        m_health -= m_hungerDamage;
    }

    if (checkDie())
    {
        //m_player->dieReason(HANGRY);
        return false;
    }

    // Clear received data
    m_received.clear();

    // Interrupts of the status
    setInterruptReason(Interrupt::LowSatiety, satietyPercent() < Constant::InterruptValueLow);
    setInterruptReason(Interrupt::MiddleSatiety, satietyPercent() < Constant::InterruptValueMiddle);
    setInterruptReason(Interrupt::LowSatiety, healthPercent() < Constant::InterruptValueLow);
    setInterruptReason(Interrupt::MiddleSatiety, healthPercent() < Constant::InterruptValueMiddle);

    return true;
}

bool Ant::checkDie()
{
    if (m_health <= 0)
    {
        m_status = Status::Dead;
    }

    return (m_status == Status::Dead);
}

};
