#include "Ant.h"

#include "jsonhelper.h"
#include "memory.h"

namespace WarAnts
{

std::string AntTypeToString(AntType type)
{
    switch (type)
    {
        case AntType::Queen: return "queen";
        case AntType::Solder: return "solder";
        case AntType::Worker: return "worker";
        default: return "?";
    }
}

Ant::Ant(const nlohmann::json& json, AntType type)
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

void Ant::reset()
{
    m_satiety = m_maxSatiety;
    m_health = m_maxHealth;
    m_cargo = 0;
}

bool Ant::damage(int16_t damage)
{
    m_health -= damage;

    if (checkDie())
    {
        return false;
    }

    setInterruptReason(Interrupt::WasAttacked, true);
}

bool Ant::beginTurn()
{
    ++m_lifeCount;
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
        return false;
    }

    // Clear received data
    m_received.clear();
    // Clear IR
    m_interruptReason = 0;
    // Copy IF form memory to variable
    m_interruptFlags = m_memory[Memory::InterruptFlags];

    // Attack
    setInterruptReason(Interrupt::LowSatiety, satietyPercent() < INTERRUPT_LOW);
    setInterruptReason(Interrupt::MiddleSatiety, satietyPercent() < INTERRUPT_MIDDLE);
    setInterruptReason(Interrupt::LowSatiety, healthPercent() < INTERRUPT_LOW);
    setInterruptReason(Interrupt::MiddleSatiety, healthPercent() < INTERRUPT_MIDDLE);

    return true;
}

bool Ant::checkDie()
{
    if (m_health <= 0)
    {
        m_status = AntStatus::Dead;
    }

    return (m_status == AntStatus::Dead);
}

};
