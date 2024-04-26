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
    m_visibility = json["visibility"];
    m_maxSatiety = json["satiety"];
    m_eatPerTurn = json.contains("ept") ? static_cast<int16_t>(json["ept"]) : 0;
    m_maxCargo = json.contains("cargo") ? static_cast<int16_t>(json["cargo"]) : 0;
    m_memory = json["memory"];
    m_workerPerTurn = json.contains("wpt") ? static_cast<int16_t>(json["wpt"]) : 0;
    m_solderPerTurn = json.contains("spt") ? static_cast<int16_t>(json["spt"]) : 0;

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