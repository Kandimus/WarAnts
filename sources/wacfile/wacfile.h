
#include <unordered_map>
#include <vector>

#include "asm_defines.h"

using PragmaMap = std::unordered_map<WarAnts::Asm::PragmaType, std::string>;

namespace WarAnts
{

bool saveWacFile(const std::string& filename, const std::vector<int8_t>& data, PragmaMap& pragma);
bool loadWacFile(const std::string& filename, std::vector<int8_t>& data, PragmaMap& pragma);

}; // namespace WarAnts
