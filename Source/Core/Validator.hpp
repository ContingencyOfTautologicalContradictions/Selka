#pragma once
#include "Shader.hpp"

namespace Selka::Validator
{
    auto Validate(std::string&&, std::string&&, Shader) -> void;

    auto Validate(std::string&&, std::string&&, Shader, std::size_t) -> void;
}