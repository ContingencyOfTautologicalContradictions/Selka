#pragma once
#include <string>

namespace Selka
{
    [[nodiscard]] auto Symlink(const std::string&) noexcept -> std::string;
}