#include "Location.hpp"

namespace Selka::Spell
{
    void from_json(const nlohmann::json& data, Location& l)
    {
        l.expansionLoc = Json::Field<ExpansionLocation>(data, "expansionLoc");
    }
}