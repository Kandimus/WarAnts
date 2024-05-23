#include "jsonhelper.h"

namespace JsonHelper
{

template<typename T>
static
T getBoundedValue(const T& value, const T& defVal, const T& minVal, const T& maxVal)
{
    if ((value < minVal || value > maxVal))
    {
        value = defVal;
    }

    if (value < minVal)
    {
        value = minVal;
    }
    if (value > maxVal)
    {
        value = maxVal;
    }
    return value;
}

template<typename T>
T getValue1(const nlohmann::json& json, const std::string& param, const T& defVal, const T& minVal, const T& maxVal)
{
    T val = getValue1<T>(json, param, defVal);
    return getBoundedValue<T>(val, defVal, minVal, maxVal);
}

template<typename T>
T getValue1(const nlohmann::json& json, const std::string& param, const T& defVal)
{
    return json.contains(param)
        ? static_cast<T>(json[param])
        : defVal;
}

template<typename T>
T getValue2(const nlohmann::json& json, const std::string& folder, const std::string& param, const T& defVal, const T& minVal, const T& maxVal)
{
    T val = (json.contains(folder) && json[folder].contains(param))
        ? static_cast<T>(json[folder][param])
        : defVal;

    return getBoundedValue<T>(val, defVal, minVal, maxVal);
}

};
