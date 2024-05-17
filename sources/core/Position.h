#pragma once

#include <stdint.h>

#include <string>
#include <vector>

namespace WarAnts
{

class Position
{
public:
    Position() = default;
    Position(const Position& p) { init(p.x(), p.y()); }
    Position(int16_t x, int16_t y) { init(x, y); }
    Position(int16_t v) { init(v, v); }
    virtual ~Position() = default;

    int16_t x() const { return m_x; }
    int16_t y() const { return m_y; }

    void init(int16_t x, int16_t y) { m_x = x; m_y = y; }
    void setX(int16_t x) { m_x = x; }
    void setY(int16_t y) { m_y = y; }
    void addX(int16_t x) { m_x += x; }
    void addY(int16_t y) { m_y += y; }
    void subX(int16_t x) { m_x -= x; }
    void subY(int16_t y) { m_y -= y; }
    void inc() { ++m_x; ++m_y; }
    void dec() { --m_x; --m_y; }
    void neg() { m_x = -m_x; m_y = -m_y; }

    bool operator==(const Position& p) const { return m_x == p.x() && m_y == p.y(); }
    bool operator!=(const Position& p) const { return m_x != p.x() || m_y != p.y(); }

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

    inline Position& operator =(int v) { m_x = m_y = static_cast<int16_t>(v); return *this; }
    inline Position& operator =(const Position& p)
    {
        setX(p.x());
        setY(p.y());

        return *this;
    }

    void operator+=(const Position& p) { m_x += p.x(); m_y += p.y(); }
    void operator-=(const Position& p) { m_x -= p.x(); m_y -= p.y(); }
    void operator*=(const Position& p) { m_x *= p.x(); m_y *= p.y(); }
    void operator/=(const Position& p) { m_x /= p.x(); m_y /= p.y(); }

    void operator+=(int16_t val) { m_x += val; m_y += val; }
    void operator-=(int16_t val) { m_x -= val; m_y -= val; }
    void operator*=(int16_t val) { m_x *= val; m_y *= val; }
    void operator/=(int16_t val) { m_x -= val; m_y -= val; }

    Position min(const Position& p) const { return Position(m_x < p.m_x ? m_x : p.m_x, m_y < p.m_y ? m_y : p.m_y); }
    Position max(const Position& p) const { return Position(m_x > p.m_x ? m_x : p.m_x, m_y > p.m_y ? m_y : p.m_y); }

    Position min(int16_t v) const { return Position(m_x < v ? m_x : v, m_y < v ? m_y : v); }
    Position max(int16_t v) const { return Position(m_x > v ? m_x : v, m_y > v ? m_y : v); }

    std::string toString() const
    {
        return "[" + std::to_string(m_x) + ", " + std::to_string(m_y) + "]";
    }

private:
    int16_t m_x = 0;
    int16_t m_y = 0;
};

using VectorPosition = std::vector<Position>;

};
