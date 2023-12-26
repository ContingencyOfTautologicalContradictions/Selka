#pragma once
#include "StringLiteral.hpp"
#include "CXXBoolLiteralExpr.hpp"

namespace Selka::Spell
{
    class [[nodiscard]] StaticAssertDecl final
    {
    public:
        using Variants = std::variant<CXXBoolLiteralExpr, StringLiteral>;

        Json::Field<std::vector<Variants>> inner;
    };

    void from_json(const nlohmann::json&, StaticAssertDecl&);
}