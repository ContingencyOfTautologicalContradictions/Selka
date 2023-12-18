#include "Symlink.hpp"
#include <filesystem>

namespace Selka
{
    [[nodiscard]] auto ResolveSymlink(const std::string& outdir) noexcept ->
    std::string
    {
        const std::string routdir = std::filesystem::read_symlink(outdir);
        return std::filesystem::is_symlink(routdir) ? ResolveSymlink(routdir) :
        routdir;
    }

    [[nodiscard]] auto Symlink(const std::string& outdir) noexcept -> std::
    string
    {
        return std::filesystem::is_symlink(outdir) ? ResolveSymlink(outdir) :
        outdir;
    }
}