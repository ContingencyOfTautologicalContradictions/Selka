#include "CXXBoolLiteralExpr.hpp"

namespace Selka::Spell
{
    void from_json(const nlohmann::json& data, CXXBoolLiteralExpr& cble)
    {
        cble.type = Json::Field<Type>(data, "type");
        cble.valueCategory = Json::Field<std::string>(data, "valueCategory");
        cble.value = Json::Field<bool>(data, "value");
    }
}