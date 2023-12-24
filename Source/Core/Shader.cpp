#include "Shader.hpp"
#include <cctype>
#include <iostream>

namespace Selka
{
    [[nodiscard]] auto ShaderLanguage(const std::string& ilang) -> Shader
    {
        std::string lang;
        for(const char c : ilang)
            lang.append(1z, std::tolower(c));
        if(lang == "hlsl")
            return Shader::HLSL;
        else if(lang == "glsl")
            return Shader::GLSL;
        else if(lang == "wgsl")
            return Shader::WGSL;
        else if(lang == "msl")
            return Shader::MSL;
        else
        {
            std::cerr << "The given shading language '" << ilang << "' is "
            "invalid, consult https://github.com/"
            "ContingencyOfTautologicalContradictions/Selka/blob/main/README.md"
            "#usage";
            std::abort();
        }
    }

    [[nodiscard]] auto ShaderLanguage(Shader shader) -> std::string
    {
        switch(shader)
        {
            using enum Shader;
            case HLSL:
                return ".hlsl";
            case GLSL:
                return ".glsl";
            case WGSL:
                return ".wgsl";
            case MSL:
                return ".metal";
        }
    }
}