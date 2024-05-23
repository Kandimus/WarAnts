#pragma once

#include "nlohmann/json.hpp"

namespace JsonHelper
{

template<typename T>
T getValue1(const nlohmann::json& json, const std::string& param, const T& defVal, const T& minVal, const T& maxVal);

template<typename T>
T getValue1(const nlohmann::json& json, const std::string& param, const T& defVal);

template<typename T>
T getValue2(const nlohmann::json& json, const std::string& folder, const std::string& param, const T& defval, const T& minVal, const T& maxVal);

};

