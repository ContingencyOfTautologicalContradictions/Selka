#pragma once
#include <string>

namespace Selka
{
    enum class Shader : std::uint8_t
    {
        WGSL,
        MSL,
        GLSL,
        HLSL
    };

    [[nodiscard]] auto ShaderLanguage(const std::string&) -> Shader;

    [[nodiscard]] auto ShaderLanguage(Shader) -> std::string;
}