#pragma once
#include "ExpansionLocation.hpp"

namespace Selka::Spell
{
    class [[nodiscard]] Location final
    {
    public:
        Json::Field<ExpansionLocation> expansionLoc;
    };

    void from_json(const nlohmann::json&, Location&);
}