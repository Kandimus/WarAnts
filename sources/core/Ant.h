#pragma once

#include <stdint.h>
#include <memory>
#include <string>
#include <vector>
#include <list>

#include "nlohmann/json.hpp"
#include "stringex.h"

#include "AntCommand.h"

namespace WarAnts
{

class Player;

using PlayerPtr = std::shared_ptr<Player>;

enum class AntType
{
    Queen = 0,
    Solder,
    Worker,

    __MAX,
};

enum class AntStatus
{
    Life = 0,
    Dead,
};

std::string AntTypeToString(AntType type);

class Ant
{
public:
    Ant() = default;
    Ant(const nlohmann::json& json, AntType type);
    Ant(const Ant& ant) = default;
    Ant(Ant&& ant) = default;
    virtual ~Ant() = default;

    Ant& operator=(const Ant& ant) = default;

public:
    uint32_t maxSatiety() const { return m_maxSatiety; }
    uint32_t satiety() const { return m_satiety; }
    uint32_t health() const { return m_health; }
    uint32_t attack() const { return m_attack; }
    uint32_t visibility() const { return m_visibility; }
    uint16_t maxCargo() const { return m_maxCargo; }
    uint16_t cargo() const { return m_cargo; }
    AntType type() const { return m_type; }
    AntStatus status() const { return m_status; }

    bool isWorker() const { return m_type == AntType::Worker; }
    bool isSolder() const { return m_type == AntType::Solder; }
    bool isQueen() const { return m_type == AntType::Queen; }

    float healthPercent() const { return m_health * 100.f / m_maxHealth; }
    float satietyPercent() const { return m_satiety * 100.f / m_maxSatiety; }
    
    //	virtual std::string strType() const = 0;
    
    void reset();

    bool hasCommand() const { return m_command.m_type != CommandType::Idle; }
    void setCommand(const AntCommand& cmd) { m_command = cmd; }
    void setCommand(CommandType cmd, int16_t x, int16_t y, int16_t userdata) { m_command.set(cmd, x, y, userdata); }
    const AntCommand& command() const { return m_command; }
    void clearCommand() { m_command.clear(); }

    std::vector<int16_t>& memory() { return m_memory; }

    uint32_t id() const { return m_id; }
    void setId(uint32_t id) { m_id = id; }

    const Position& position() const { return m_pos; }
    void setPosition(const Position& pos) { m_pos = pos; }

    PlayerPtr player() const { return m_player; }
    void setPlayer(PlayerPtr player) { m_player = player; }

    bool damage(int16_t damage);

    bool beginTurn();
    bool endTurn();

    uint32_t lifeCount() const { return m_lifeCount; }

    std::string getString() const
    {
        return su::String_format("#%i");
    }

protected:
    bool checkDie();

protected:
    uint32_t m_id = 0;
    AntType m_type = AntType::Worker;
    Position m_pos = 0;
    AntStatus m_status = AntStatus::Life;
    //    bool m_isFight;
    int16_t m_maxSatiety = 0;
    int16_t m_satiety = 0;
    int16_t m_maxHealth = 0;
    int16_t m_health = 0;
    int16_t m_attack = 0;
    int16_t m_visibility = 25;
    int16_t m_maxCargo = 0;
    int16_t m_cargo = 0;
    int8_t m_eatPerTurn = 1;
    int8_t m_turnToWorker = 0;
    int8_t m_turnToSolder = 0;
    int8_t m_sizeOfMemory = 8;

    AntCommand m_command;
    PlayerPtr m_player;
    std::vector<int16_t> m_memory;
    
    // statistic
    uint32_t m_lifeCount = 0;
};

using AntPtr = std::shared_ptr<Ant>;
using VectorAnts = std::vector<std::shared_ptr<Ant>>;
using ListAnts = std::list<std::shared_ptr<Ant>>;

};
