#pragma once
#include "../Json/Field.hpp"

namespace Selka::Spell
{
    class [[nodiscard]] Type final
    {
    public:
        Json::Field<std::string> qualType;
    };

    void from_json(const nlohmann::json&, Type&);
}