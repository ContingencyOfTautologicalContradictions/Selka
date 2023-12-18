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

    [[nodiscard]] auto ShaderLanguage(const std::string&) noexcept -> Shader;
}