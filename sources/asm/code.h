#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "asm_defines.h"

namespace WarAnts
{
namespace Asm
{

struct Function;
struct Pragma;

class Code
{
public:
    Code() = default;
    virtual ~Code() = default;

    void init()
    {
        m_pragma.clear();
        m_pragma.reserve(32);

        m_defines.clear();
        m_defines.reserve(32);


        m_function.clear();
        m_function.reserve(32);
    }

    void addPragma(const std::shared_ptr<Pragma>& pragma)
    {
        m_pragma.push_back(pragma);
    }

    void addDefine(const std::string& label, int16_t value)
    {
        m_defines[label] = value;
    }

    int16_t define(const std::string& label) const
    {
        return m_defines[label];
    }

    bool containsDefine(const std::string& label) const
    {
        return m_defines.find(label) != m_defines.end();
    }


public:
    std::vector<std::shared_ptr<Pragma>> m_pragma;
    std::vector<std::shared_ptr<Function>> m_function;
    std::unordered_map<std::string, int16_t> m_defines;
};

}; // namespace Asm
}; // namespace WarAnts
