#pragma once
#include "Type.hpp"
#include "../Core/ShaderKind.hpp"

namespace Selka::Spell
{
    class [[nodiscard]] FunctionDecl final
    {
    public:
        auto Shade(std::string&, ShaderKind&) const -> void;

        Json::Field<std::string> name;

        Json::Field<Type> type;
    };

    void from_json(const nlohmann::json&, FunctionDecl&);
}