#include "ExpansionLocation.hpp"

namespace Selka::Spell
{
    void from_json(const nlohmann::json& data, ExpansionLocation& el)
    {
        el.file = Json::Field<std::string>(data, "file");
        el.line = Json::Field<std::uint64_t>(data, "line");
        el.col = Json::Field<std::uint64_t>(data, "col");
    }
}