#pragma once

#include <vector>

#include "MapMath.h"

namespace WarAnts
{

template<typename T>
class vectorMin
{
public:
    vectorMin() = default;
    virtual ~vectorMin() = default;

    void add(const T& t, size_t v)
    {
        if (v < minimum)
        {
            minimum = v;
            items.clear();
            items.push_back(t);
            return;
        }
        if (v == minimum)
        {
            items.push_back(t);
            return;
        }
    }
    size_t value() const { return minimum; }
    const T& randomIndex() const { return items[Math::random(0, items.size() - 1)]; }

    void push_back(const T& t) { items.push_back(t); }
    void push_back(T&& t) { items.push_back(t); }
    size_t size() const { return items.size(); }
    auto begin() noexcept { return items.begin(); }
    auto end() noexcept { return items.end(); }
    bool empty() const noexcept { return items.empty(); }

    T& operator[](size_t v) noexcept { return items[v]; }
    const T& operator[](size_t v) const noexcept { return items[v]; }

public:
    std::vector<T> items;
    size_t minimum = 0xffffffffffffffff;
};

} //namespace WarAnts
