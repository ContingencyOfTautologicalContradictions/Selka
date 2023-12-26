#pragma once
#include "../Json/Field.hpp"

namespace Selka::Spell
{
    class [[nodiscard]] ExpansionLocation final
    {
    public:
        Json::Field<std::string> file;

        Json::Field<std::uint64_t> line, col;
    };

    void from_json(const nlohmann::json&, ExpansionLocation&);
}