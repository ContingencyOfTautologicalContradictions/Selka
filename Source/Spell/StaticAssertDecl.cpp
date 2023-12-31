#include "StaticAssertDecl.hpp"

namespace Selka::Spell
{
    auto Assign(bool& stop, const Json::Field<Location>& loc, ShaderKind&
    shader, const Type& type, const Json::Field<std::string>& valueCategory,
    const Json::Field<std::string>& value) -> void
    {
        if(type.qualType.Present())
            if(type.qualType.Value() == "NULL TYPE")
                if(valueCategory.Present())
                    if(valueCategory.Value() == "lvalue")
                        if(value.Present())
                        {
                            if(value.Value() == "\"selka.shading.vertex\"" and
                            loc.Present())
                            {
                                stop = true;
                                shader.kind = Kind::Vertex;
                                shader.loc = loc.Value();
                            }
                            else if(value.Value() ==
                            "\"selka.shading.fragment\"" and loc.Present())
                            {
                                stop = true;
                                shader.kind = Kind::Fragment;
                                shader.loc = loc.Value();
                            }
                            else if(value.Value().starts_with(
                            "\"selka.shading.compute ") and value.Value().
                            ends_with('"') and loc.Present())
                            {
                                stop = true;
                                shader.kind = Kind::Compute;
                                shader.loc = loc.Value();
                                std::string dim;
                                std::uint8_t mode = 0u;
                                for(std::size_t x = 23z; x < value.Value().size
                                (); ++x)
                                {
                                    char c = value.Value()[x];
                                    switch(mode)
                                    {
                                        case 0u:
                                            if(c == ':')
                                            {
                                                mode = 1u;
                                                shader.x = std::stoull(dim);
                                                dim.clear();
                                            }
                                            else
                                                dim.append(1z, c);
                                        break;
                                        case 1u:
                                            if(c == ':')
                                            {
                                                mode = 2u;
                                                shader.y = std::stoull(dim);
                                                dim.clear();
                                            }
                                            else
                                                dim.append(1z, c);
                                        break;
                                        case 2u:
                                            if(c == '"')
                                                shader.z = std::stoull(dim);
                                            else
                                                dim.append(1z, c);
                                        break;
                                    }
                                }
                            }
                        }
    }

    auto StaticAssertDecl::Shade(std::string& source, ShaderKind& sk) const ->
    void
    {
        bool stop = false;
        if(inner.Value().size() == 2z)
            std::visit([&](auto&& element)
            {
                using T = std::decay_t<decltype(element)>;
                if constexpr(Meta::Same<T, CXXBoolLiteralExpr>)
                    if(element.type.Present())
                        if(element.type.Value().qualType.Present())
                            if(element.type.Value().qualType.Value() == "bool")
                                if(element.valueCategory.Present())
                                    if(element.valueCategory.Value() ==
                                    "prvalue")
                                        if(element.value.Present())
                                            if(element.value.Value())
                                                std::visit([&](auto&& selement)
                                                {
                                                    using T = std::decay_t<
                                                    decltype(selement)>;
                                                    if constexpr(Meta::Same<T,
                                                    StringLiteral>)
                                                        if(selement.type.
                                                        Present())
                                                            Assign(stop, loc,
                                                            sk, selement.type.
                                                            Value(), selement.
                                                            valueCategory,
                                                            selement.value);
                                                }, inner.Value()[1z]);
            }, inner.Value()[0z]);
        if(not stop)
        {}
    }

    void from_json(const nlohmann::json& data, StaticAssertDecl& sad)
    {
        sad.loc = Json::Field<Location>(data, "loc");
        if(data.contains("inner"))
        {
            sad.inner.Set();
            const nlohmann::json& inner = data.at("inner");
            for(const nlohmann::json& element : inner)
                if(element.contains("kind"))
                {
                    const nlohmann::json& kind = element.at("kind");
                    if(kind.is_string())
                    {
                        const std::string skind = element.at("kind").get<std::
                        string>();
                        StaticAssertDecl::Variants variant;
                        if(skind == "CXXBoolLiteralExpr")
                            variant = element.get<CXXBoolLiteralExpr>();
                        else if(skind == "StringLiteral")
                            variant = element.get<StringLiteral>();
                        sad.inner.Value().push_back(variant);
                    }
                }
        }
    }
}