#include "StaticAssertDecl.hpp"

namespace Selka::Spell
{
    void from_json(const nlohmann::json& data, StaticAssertDecl& sad)
    {
        if(data.contains("inner"))
        {
            sad.inner.Set();
            const nlohmann::json& inner = data.at("inner");
            for(const nlohmann::json& element : inner)
                if(element.contains("kind"))
                {
                    const std::string kind = element.at("kind").get<std::string
                    >();
                    StaticAssertDecl::Variants variant;
                    if(kind == "CXXBoolLiteralExpr")
                        variant = element.get<CXXBoolLiteralExpr>();
                    else if(kind == "StringLiteral")
                        variant = element.get<StringLiteral>();
                    sad.inner.Value().push_back(variant);
                }
        }
    }
}