#pragma once

#include <stdint.h>
#include <memory>
#include <string>
#include <vector>
#include <list>

#include "nlohmann/json.hpp"
#include "stringex.h"
#include "uniint.h"

#include "AntDefinition.h"
#include "AntCommand.h"

namespace WarAnts
{

class Player;
using PlayerPtr = std::shared_ptr<Player>;

class Ant : public AntDefinition
{
public:
    Ant() = default;
    Ant(const nlohmann::json& json, Type type);
    Ant(const Ant& ant) = default;
    Ant(Ant&& ant) = default;
    virtual ~Ant() = default;

    Ant& operator=(const Ant& ant) = default;

public:
    uint16_t maxSatiety() const { return m_maxSatiety; }
    uint16_t satiety() const { return m_satiety; }
    uint16_t health() const { return m_health; }
    uint16_t attack() const { return m_attack; }
    uint16_t visibility() const { return m_visibility; }
    uint16_t maxCargo() const { return m_maxCargo; }
    uint16_t cargo() const { return m_cargo; }
    Type type() const { return m_type; }
    std::string typeToString() const;
    Status status() const { return m_status; }
    int16_t foodPerTurn() const { return m_foodPerTurn; }
    int16_t turnToWorker() const { return m_turnToWorker; }
    int16_t turnToSolder() const { return m_turnToSolder; }

    bool isWorker() const { return m_type == Type::Worker; }
    bool isSolder() const { return m_type == Type::Solder; }
    bool isQueen() const { return m_type == Type::Queen; }
    bool isUnderAttack() const { return m_isUnderAttack; }

    float healthPercent() const { return m_health * 100.f / m_maxHealth; }
    float satietyPercent() const { return m_satiety * 100.f / m_maxSatiety; }
    float cargoPercent() const { return m_cargo * 100.f / m_maxCargo; }
    
    //	virtual std::string strType() const = 0;
    
    void reset();

    AntCommand& command() { return m_command; }

    int16_t getValue(size_t idx) const { return idx < m_memory.size() ? m_memory[idx] : 0; }
    void setValue(size_t idx, int16_t val) { if (idx < m_memory.size()) m_memory[idx] = val; }
    void incValue(size_t idx) { if (idx < m_memory.size()) ++m_memory[idx]; }
    std::vector<int16_t>& memory() { return m_memory; }

    su::UniInt64 getReceivedData(size_t val) const { return val < m_received.size() ? m_received[val] : su::UniInt64(0); }
    const std::vector<su::UniInt64>& receivedData() const { return m_received; }

    uint32_t id() const { return m_id; }
    void setId(uint32_t id) { m_id = id; }

    const Position& position() const { return m_pos; }
    void setPosition(const Position& pos) { m_pos = pos; }

    PlayerPtr player() const { return m_player; }
    void setPlayer(PlayerPtr player) { m_player = player; }

    // Interrupt
    inline int16_t interruptFlags() const { return m_interruptFlags; }
    inline void setInterruptFlags(int16_t val) { m_interruptFlags = val; }
    inline int16_t interruptReason() const { return m_interruptReason; }
    inline void setInterruptReason(int16_t bit, bool reason) { m_interruptReason |= ((m_interruptFlags & bit) && reason) ? bit : 0; }

    bool damage(Ant& ant);
    void kill(DeathReason reason);
    void killed(Type type);
    void clearCargo() { m_cargo = 0; }
    void modifyCargo(int16_t val) { m_cargo = (m_cargo + val) > 0 ? m_cargo + val : 0; }
    int16_t eat(int16_t food);
    int16_t eatFromCargo();
    int16_t cater(Ant& ant);

    bool beginTurn();
    bool postVM();
    bool endTurn();

    uint32_t lifeCount() const { return m_lifeCount; }

    std::string toString() const;

protected:
    bool checkDie();
    int16_t missingSatiety() const { return m_maxSatiety - m_satiety; }

protected:
    uint32_t m_id = 0;
    Type m_type = Type::Worker;
    Position m_pos = 0;
    Status m_status = Status::Life;
    DeathReason m_deathReason = DeathReason::StillAlife;
    int16_t m_maxSatiety = 0;
    int16_t m_satiety = 0;
    int16_t m_maxHealth = 0;
    int16_t m_health = 0;
    int16_t m_attack = 0;
    int16_t m_visibility = 25;
    int16_t m_maxCargo = 0;
    int16_t m_cargo = 0;
    int16_t m_redicedSatiety = 1;
    int16_t m_hungerDamage = 1;
    int16_t m_foodPerTurn = 10; // How much food can the ant eat/take/feed per turn
    int16_t m_turnToWorker = 0;
    int16_t m_turnToSolder = 0;
    int16_t m_sizeOfMemory = 8;
    std::vector<su::UniInt64> m_received; //TODO clear up after calling vm.run
    int16_t m_interruptFlags = 0;
    int16_t m_interruptReason = Interrupt::CommandAborted | Interrupt::CommandCompleted;
    bool    m_isUnderAttack = false;

    AntCommand m_command;
    PlayerPtr m_player;
    std::vector<int16_t> m_memory;
    
    // statistic
    uint32_t m_lifeCount = 0;
    uint32_t m_killed[Type::__MAX]{0};
};

using AntPtr = std::shared_ptr<Ant>;
using VectorAnts = std::vector<std::shared_ptr<Ant>>;
using ListAnts = std::list<std::shared_ptr<Ant>>;

std::string AntTypeToString(Ant::Type type);

};
