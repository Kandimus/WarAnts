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

enum class AntType
{
    Queen = 0,
    Solder,
    Worker,

    __MAX,
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
    uint32_t maxCargo() const { return m_maxCargo; }
    uint32_t cargo() const { return m_cargo; }
    AntType type() const { return m_type; }

    bool isWorker() const { return m_type == AntType::Worker; }
    bool isSolder() const { return m_type == AntType::Solder; }
    bool isQueen() const { return m_type == AntType::Queen; }

    float healthPercent() const { return m_health * 100.f / m_maxHealth; }
    float satietyPercent() const { return m_satiety * 100.f / m_maxSatiety; }
    
    //	virtual std::string strType() const = 0;
    
    void reset();

    //process(AntInfo& ai, Command& cmd);

    //double satietyPercent();
    //double healthPercent();

    bool hasCommand() const { return m_command.m_type != CommandType::Idle; }
    void setCommand(const AntCommand& cmd) { m_command = cmd; }
    void setCommand(CommandType cmd, int16_t x, int16_t y, int16_t userdata) { m_command.set(cmd, x, y, userdata); }
    const AntCommand& command() const { return m_command; }
    void clearCommand() { m_command.clear(); }

    uint32_t id() const { return m_id; }
    void setId(uint32_t id) { m_id = id; }

    const Position& position() const { return m_pos; }
    void setPosition(const Position& pos) { m_pos = pos; }

    const Player* player() const { return m_player; }
    void setPlayer(const Player* player) { m_player = player; }

//    std::weak_ptr<Player> player() const;
//    void setPlayer(std::weak_ptr<Player> player);

    bool endTurn();

    std::string getString() const
    {
        return su::String_format("#%i");
    }

protected:
    uint32_t m_id;
    AntType m_type = AntType::Worker;
    Position m_pos;
    //	Status m_status;
    //    bool m_isFight;
    int16_t m_maxSatiety = 0;
    int16_t m_satiety = 0;
    int16_t m_maxHealth = 0;
    int16_t m_health = 0;
    int16_t m_attack = 0;
    int16_t m_visibility = 0;
    int16_t m_maxCargo = 0;
    int16_t m_cargo = 0;
    int8_t m_eatPerTurn = 1;
    int8_t m_workerPerTurn = 0;
    int8_t m_solderPerTurn = 0;
    int8_t m_memory = 4;

    AntCommand m_command;
    const Player* m_player = nullptr;
    //AntProcess m_fnProcess = nullptr;
};

using AntPtr = std::shared_ptr<Ant>;
using VectorAnts = std::vector<std::shared_ptr<Ant>>;
using ListAnts = std::list<std::shared_ptr<Ant>>;

};
