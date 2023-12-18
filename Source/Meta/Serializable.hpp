#pragma once
#include "Same.hpp"
#include "../Json/Json.hpp"

namespace Selka::Meta
{
    template<class T> concept Serializable = requires (const nlohmann::json& data)
    {
        {data.get<T>()} -> Meta::Same<T>;
    };
}