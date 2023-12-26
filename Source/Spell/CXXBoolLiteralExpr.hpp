#pragma once
#include "Type.hpp"

namespace Selka::Spell
{
    class [[nodiscard]] CXXBoolLiteralExpr final
    {
    public:
        Json::Field<Type> type;

        Json::Field<std::string> valueCategory;

        Json::Field<bool> value;
    };

    void from_json(const nlohmann::json&, CXXBoolLiteralExpr&);
}