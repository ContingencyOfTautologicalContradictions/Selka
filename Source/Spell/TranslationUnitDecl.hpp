#pragma once
#include "StaticAssertDecl.hpp"

namespace Selka::Spell
{
    class [[nodiscard]] TranslationUnitDecl final
    {
    public:
        auto Shade(std::string&) const -> void;

        using Variants = std::variant<StaticAssertDecl>;

        Json::Field<std::vector<Variants>> inner;
    };

    void from_json(const nlohmann::json&, TranslationUnitDecl&);
}