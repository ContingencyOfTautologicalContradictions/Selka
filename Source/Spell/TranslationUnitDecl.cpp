#include "TranslationUnitDecl.hpp"

namespace Selka::Spell
{
    auto TranslationUnitDecl::Shade(std::string& source) const -> void
    {
        for(const Variants& variant : inner.Value())
            std::visit([&](auto&& element)
            {
                element.Shade(source);
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