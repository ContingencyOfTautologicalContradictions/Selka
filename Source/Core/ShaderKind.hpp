#pragma once
#include "../Spell/Location.hpp"

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
        Spell::Location loc;

        std::uint64_t x, y, z;

        Kind kind;
    };
}