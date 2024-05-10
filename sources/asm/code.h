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

    uint16_t updateOffset(uint16_t addOffset);

    bool checkFunctionsAndNames();
    bool extrudeExpression();
    bool checkExitStatement();
    bool compile();
    bool calculationJumpsAndCalls();
    bool assignOffsets();
    bool resolveLabels(bool& recalc);
    bool save(const std::string& filename);
    void print(const std::string& filename);
    void printData(const std::string& filename);

    Function* getFunction(const std::string& name) const;

    uint32_t offset() const { return (uint32_t)m_data.size(); }

    void addCode(int8_t val) { m_data.push_back(val); }

    std::string getPragma(PragmaType type) const;

public:
    const std::string FuncNameQueen = "queen";
    const std::string FuncNameSolder = "solder";
    const std::string FuncNameWorker = "worker";

    Function* m_funcQueen = nullptr;
    Function* m_funcSolder = nullptr;
    Function* m_funcWorker = nullptr;

    Pragma* m_pragma = nullptr;
    Function* m_function = nullptr;

    std::vector<int8_t> m_data;
    std::vector<std::string> m_errors;
    std::unordered_map<std::string, int16_t> m_defines;
};

}; // namespace Asm
}; // namespace WarAnts
