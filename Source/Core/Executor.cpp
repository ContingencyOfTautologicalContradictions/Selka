#include "Executor.hpp"
#include "../Spell/TranslationUnitDecl.hpp"
#include <iostream>

namespace Selka::Executor
{
    auto Process(std::string& content, Shader shader) -> void
    {
        const nlohmann::json data = nlohmann::json::parse(content);
        if(not data.is_object())
        {
            std::cerr << "The following JSON content ain't a valid JSON object"
            ":\n\n" << content;
            std::abort();
        }
        else if(data.contains("kind"))
        {
            const nlohmann::json& kind = data.at("kind");
            if(kind.is_string())
            {
                if(kind.get<std::string>() == "TranslationUnitDecl")
                    data.get<Spell::TranslationUnitDecl>().Shade(content,
                    shader);
                else
                {
                    std::cerr << "The following JSON content ain't a valid "
                    "JSON object:\n\n" << content;
                    std::abort();
                }
            }
            else
            {
                std::cerr << "The following JSON content ain't a valid JSON "
                "object:\n\n" << content;
                std::abort();
            }
        }
        else
        {
            std::cerr << "The following JSON content ain't a valid JSON object"
            ":\n\n" << content;
            std::abort();
        }
    }
}