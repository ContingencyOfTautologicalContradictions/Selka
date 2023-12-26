#pragma once
#include "StringLiteral.hpp"
#include "../Core/ShaderKind.hpp"
#include "CXXBoolLiteralExpr.hpp"

namespace Selka::Spell
{
    class [[nodiscard]] StaticAssertDecl final
    {
    public:
        auto Shade(std::string&, ShaderKind&) const -> void;

        using Variants = std::variant<CXXBoolLiteralExpr, StringLiteral>;

        Json::Field<std::vector<Variants>> inner;
    };

    void from_json(const nlohmann::json&, StaticAssertDecl&);
}