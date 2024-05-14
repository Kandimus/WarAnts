#pragma once

#include <stdint.h>
#include <memory>

namespace WarAnts
{

class Ant;
class Map;
class Player;

class VirtualMachine
{
public:
    VirtualMachine(const std::shared_ptr<Map>& map)
        : m_map(map)
    {}
    VirtualMachine(const VirtualMachine&) = delete;
    VirtualMachine(VirtualMachine&&) = delete;
    virtual ~VirtualMachine() = default;

    VirtualMachine& operator=(const VirtualMachine& ant) = delete;

public:
    bool run(const std::shared_ptr<Ant>& ant);

protected:
    std::shared_ptr<Map> m_map;
};

//using AntPtr = std::shared_ptr<Ant>;
//using VectorAnts = std::vector<std::shared_ptr<Ant>>;
//using ListAnts = std::list<std::shared_ptr<Ant>>;

};
