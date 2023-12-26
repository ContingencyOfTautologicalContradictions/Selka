#pragma once
#include <cstdint>

namespace Selka
{
    enum class Kind : std::uint8_t
    {
        None,
        Vertex,
        Fragment,
        Compute
    };

    class [[nodiscard]] ShaderKind final
    {
    public:
        std::uint64_t x, y, z;

        Kind kind;
    };
}