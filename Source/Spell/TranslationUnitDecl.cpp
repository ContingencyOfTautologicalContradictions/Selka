#include "TranslationUnitDecl.hpp"

namespace Selka::Spell
{
    auto TranslationUnitDecl::Shade(std::string& source, Shader shader) const
    -> void
    {
        bool Vertex = false;
        for(const Variants& variant : inner.Value())
            std::visit([&](auto&& element)
            {
                using T = std::decay_t<decltype(element)>;
                if constexpr(Meta::Same<T, StaticAssertDecl>)
                    element.Shade(source, Vertex);
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
                        tud.inner.Value().push_back(variant);
                    }
                }
        }
    }
}