#include "Executor.hpp"
#include "../Spell/TranslationUnitDecl.hpp"
#include <iostream>

namespace Selka::Executor
{
    void Process(std::string& content)
    {
        const nlohmann::json data = nlohmann::json::parse(content);
        if(not data.is_object())
        {
            std::cerr << "The following JSON content ain't a valid JSON object"
            ":\n\n" << content;
            std::abort();
        }
        content.clear();
        data.get<Spell::TranslationUnitDecl>().Shade(content);
    }
}