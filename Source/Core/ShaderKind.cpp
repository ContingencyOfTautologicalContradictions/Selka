#include "ShaderKind.hpp"

namespace Selka
{
    [[nodiscard]] auto ShadeKind(Kind sk) -> std::string
    {
        switch(sk)
        {
            using enum Kind;
            case None:
                return "";
            case Vertex:
                return "vertex";
            case Fragment:
                return "fragment";
            case Compute:
                return "compute";
        }
    }
}