#include "Type.hpp"

namespace Selka::Spell
{
    void from_json(const nlohmann::json& data, Type& t)
    {
        t.qualType = Json::Field<std::string>(data, "qualType");
    }
}