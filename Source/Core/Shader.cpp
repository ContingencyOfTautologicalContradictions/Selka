#include "Shader.hpp"

namespace Selka
{
    [[nodiscard]] auto ShaderLanguage(const std::string& lang) noexcept ->
    Shader
    {
        if(lang == "hlsl")
            return Shader::HLSL;
        else if(lang == "glsl")
            return Shader::GLSL;
        else if(lang == "wgsl")
            return Shader::WGSL;
        else if(lang == "msl")
            return Shader::MSL;
        else
            std::abort();
    }
}