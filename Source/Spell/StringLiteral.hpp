#pragma once
#include "Type.hpp"

namespace Selka::Spell
{
    class [[nodiscard]] StringLiteral final
    {
    public:
        Json::Field<Type> type;

        Json::Field<std::string> valueCategory, value;
    };

    void from_json(const nlohmann::json&, StringLiteral&);
}