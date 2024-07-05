#pragma once

#include <stdint.h>

#include <string>
#include <vector>
#include "uniint.h"

namespace WarAnts
{

struct Position
{
    Position() = default;
    Position(const Position& p) { init(p.x(), p.y()); }
    Position(int16_t x, int16_t y) { init(x, y); }
    Position(int16_t v) { init(v, v); }
    virtual ~Position() = default;

    inline int16_t x() const { return value.i16[0]; }
    inline int16_t y() const { return value.i16[1]; }

    inline void init(int16_t x, int16_t y) { value.i16[0] = x; value.i16[1] = y; }
    inline void setX(int16_t x) { value.i16[0] = x; }
    inline void setY(int16_t y) { value.i16[1] = y; }
    inline void addX(int16_t x) { value.i16[0] += x; }
    inline void addY(int16_t y) { value.i16[1] += y; }
    inline void subX(int16_t x) { value.i16[0] -= x; }
    inline void subY(int16_t y) { value.i16[1] -= y; }
    inline void inc() { ++value.i16[0]; ++value.i16[1]; }
    inline void dec() { --value.i16[0]; --value.i16[1]; }
    inline void neg() { value.i16[0] = -value.i16[0]; value.i16[1] = -value.i16[1]; }

    Position min(const Position& p) const { return Position(std::min(x(), p.x()), std::min(y(), p.y())); }
    Position max(const Position& p) const { return Position(std::max(x(), p.x()), std::max(y(), p.y())); }

    Position min(int16_t v) const { return Position(std::min(x(), v), std::min(y() ,v)); }
    Position max(int16_t v) const { return Position(std::max(x(), v), std::max(y(), v)); }

    Position abs() const { return Position(std::abs(x()), std::abs(y())); }
    
    int16_t minAxis() const { return std::min(x(), y()); }
    int16_t maxAxis() const { return std::max(x(), y()); }

    void store(int16_t* p) const { p[0] = x(); p[1] = y(); }

    bool operator==(const Position& p) const { return x() == p.x() && y() == p.y(); }
    bool operator!=(const Position& p) const { return x() != p.x() || y() != p.y(); }

    Position operator+(const Position& p) const
    {
        Position out(*this);

        out.addX(p.x());
        out.addY(p.y());

        return out;
    }
    Position operator-(const Position& p) const
    {
        Position out(*this);

        out.subX(p.x());
        out.subY(p.y());

        return out;
    }
    Position operator*(int16_t len) const
    {
        Position out(*this);

        out.setX(out.x() * len);
        out.setY(out.y() * len);

        return out;
    }

    inline Position& operator =(int v) { value.i16[0] = value.i16[1] = static_cast<int16_t>(v); return *this; }
    inline Position& operator =(const Position& p)
    {
        setX(p.x());
        setY(p.y());

        return *this;
    }

    void operator+=(const Position& p) { value.i16[0] += p.x(); value.i16[1] += p.y(); }
    void operator-=(const Position& p) { value.i16[0] -= p.x(); value.i16[1] -= p.y(); }
    void operator*=(const Position& p) { value.i16[0] *= p.x(); value.i16[1] *= p.y(); }
    void operator/=(const Position& p) { value.i16[0] /= p.x(); value.i16[1] /= p.y(); }

    void operator+=(int16_t val) { value.i16[0] += val; value.i16[1] += val; }
    void operator-=(int16_t val) { value.i16[0] -= val; value.i16[1] -= val; }
    void operator*=(int16_t val) { value.i16[0] *= val; value.i16[1] *= val; }
    void operator/=(int16_t val) { value.i16[0] -= val; value.i16[1] -= val; }

    std::string toString() const
    {
        return "<" + std::to_string(x()) + ", " + std::to_string(y()) + ">";
    }

private:
    su::UniInt32 value = {0};
};

using VectorPosition = std::vector<Position>;

};
