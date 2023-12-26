#include "StringLiteral.hpp"

namespace Selka::Spell
{
    void from_json(const nlohmann::json& data, StringLiteral& sl)
    {
        sl.type = Json::Field<Type>(data, "type");
        sl.valueCategory = Json::Field<std::string>(data, "valueCategory");
        sl.value = Json::Field<std::string>(data, "value");
    }
}