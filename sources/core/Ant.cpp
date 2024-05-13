#include "Ant.h"

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
    m_maxHealth = json.contains("health") ? static_cast<int16_t>(json["health"]) : 1;
    m_attack = json["attack"];
    m_visibility = json.contains("visibility") ? static_cast<int16_t>(json["visibility"]) : m_visibility;
    m_maxSatiety = json["satiety"];
    m_eatPerTurn = json.contains("ept") ? static_cast<int16_t>(json["ept"]) : m_eatPerTurn;
    m_maxCargo = json.contains("cargo") ? static_cast<int16_t>(json["cargo"]) : m_maxCargo;
    m_sizeOfMemory = json.contains("memory") ? static_cast<int16_t>(json["memory"]) : m_sizeOfMemory;
    m_turnToSolder = json.contains("solder") ? static_cast<int16_t>(json["solder"]) : m_turnToSolder;
    m_turnToWorker = json.contains("worker") ? static_cast<int16_t>(json["worker"]) : m_turnToWorker;

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

    return checkDie();
}

bool Ant::beginTurn()
{
    ++m_lifeCount;
    return true;
}

bool Ant::endTurn()
{
    m_satiety -= m_eatPerTurn;

    if (m_satiety <= 0)
    {
        m_satiety = 0;
        --m_health;
    }

    return checkDie();
}

bool Ant::checkDie()
{
    if (m_health <= 0)
    {
        m_status = AntStatus::Dead;
    }

    return (m_status == AntStatus::Life);
}

};
