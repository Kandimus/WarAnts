#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "baseNode.h"

namespace WarAnts
{
namespace Asm
{

class Function;
class Pragma;

class Code : public BaseNode
{
public:
    Code() : BaseNode(nullptr) {}
    virtual ~Code() = default;

    void error(const char* format, ...);
    void error(uint32_t lineno, const char* format, ...);
    bool hasError() const { return m_errors.size() > 0; }

    bool checkFunctionsAndNames();
    bool extrudeExpression();
    bool compile();
    bool calculationJumpsAndCalls();
    bool assignOffsets();
    bool resolveLabels(bool& recalc);
    void print(const std::string& filename);

    Function* getFunction(const std::string& name) const;
    

    uint32_t offset() const
    {
        return (uint32_t)m_data.size();
    }

    void addCode(int8_t val)
    {
        m_data.push_back(val);
    }

public:
    const std::string FuncNameQueen = "queen";
    const std::string FuncNameSolder = "solder";
    const std::string FuncNameWorker = "worker";

    Pragma* m_pragma = nullptr;
    Function* m_function = nullptr;

    std::vector<int8_t> m_data;
    std::vector<std::string> m_errors;
    std::unordered_map<std::string, int16_t> m_defines;
};

}; // namespace Asm
}; // namespace WarAnts
