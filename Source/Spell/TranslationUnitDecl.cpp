#include "TranslationUnitDecl.hpp"
#include <iostream>

namespace Selka::Spell
{
    auto TranslationUnitDecl::Shade(std::string& source, Shader shader) const
    -> void
    {
        ShaderKind sk;
        for(const Variants& variant : inner.Value())
            std::visit([&](auto&& element)
            {
                using T = std::decay_t<decltype(element)>;
                switch(sk.kind)
                {
                    using enum Kind;
                    case Vertex:
                    case Fragment:
                    case Compute:
                        if constexpr(Meta::Same<T, FunctionDecl>)
                        {
                            element.Shade(source, sk);
                            sk.kind = Kind::None;
                        }
                        else if(sk.loc.expansionLoc.Present() and sk.loc.
                        expansionLoc.Value().file.Present() and sk.loc.
                        expansionLoc.Value().line.Present() and sk.loc.
                        expansionLoc.Value().col.Present())
                        {
                            std::cerr << "error: The '" + ShadeKind(sk.kind) +
                            "' keyword at '" + sk.loc.expansionLoc.Value().file
                            .Value() + ", " + std::to_string(sk.loc.
                            expansionLoc.Value().line.Value()) + " : " + std::
                            to_string(sk.loc.expansionLoc.Value().col.Value())
                            + "' must be followed by a function";
                            std::abort();
                        }
                    break;
                    case None:
                        if constexpr(Meta::Same<T, StaticAssertDecl>)
                            element.Shade(source, sk);
                    break;
                }
            }, variant);
    }

    void from_json(const nlohmann::json& data, TranslationUnitDecl& tud)
    {
        if(data.contains("inner"))
        {
            tud.inner.Set();
            const nlohmann::json& inner = data.at("inner");
            for(const nlohmann::json& element : inner)
                if(element.contains("kind"))
                {
                    const nlohmann::json& kind = element.at("kind");
                    if(kind.is_string())
                    {
                        const std::string skind = kind.get<std::string>();
                        TranslationUnitDecl::Variants variant;
                        if(skind == "TypedefDecl")
                        {
                            if(element.contains("isImplicit"))
                            {
                                const nlohmann::json& isImplicit = element.at(
                                "isImplicit");
                                if(isImplicit.is_boolean())
                                    if(isImplicit.get<bool>())
                                        continue;
                            }
                        }
                        else if(skind == "StaticAssertDecl")
                            variant = element.get<StaticAssertDecl>();
                        else if(skind == "FunctionDecl")
                            variant = element.get<FunctionDecl>();
                        tud.inner.Value().push_back(variant);
                    }
                }
        }
    }
}