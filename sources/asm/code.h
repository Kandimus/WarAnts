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

    bool checkFunctionName();
    bool moveLabelToStatetment();

public:
    const std::string FuncNameQueen = "queen";
    const std::string FuncNameSolder = "solder";
    const std::string FuncNameWorker = "worker";

    Pragma* m_pragma = nullptr;
    Function* m_function = nullptr;

    std::vector<std::string> m_errors;
    std::unordered_map<std::string, int16_t> m_defines;
};

}; // namespace Asm
}; // namespace WarAnts
