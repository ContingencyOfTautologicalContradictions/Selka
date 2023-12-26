#pragma once
#include "FunctionDecl.hpp"
#include "../Core/Shader.hpp"
#include "StaticAssertDecl.hpp"

namespace Selka::Spell
{
    class [[nodiscard]] TranslationUnitDecl final
    {
    public:
        auto Shade(std::string&, Shader) const -> void;

        using Variants = std::variant<StaticAssertDecl, FunctionDecl>;

        Json::Field<std::vector<Variants>> inner;
    };

    void from_json(const nlohmann::json&, TranslationUnitDecl&);
}