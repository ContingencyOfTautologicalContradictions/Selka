#include "Symlink.hpp"
#include "Validator.hpp"
#include "Scheduler.hpp"
#include <filesystem>
#include <fstream>

namespace Selka::Validator
{
    auto Validate(std::string&& input, std::string&& outdir, Shader shader) ->
    void
    {
        const std::filesystem::directory_iterator files(std::filesystem::path(input), std::filesystem
        ::directory_options::follow_directory_symlink);
        Scheduler scheduler(std::forward<std::string>(outdir), shader);
        for(const std::filesystem::directory_entry& a : files)
        {
            std::string file = Symlink(a.path());
            if(file.ends_with(".selka"))
            {
                const std::size_t content_size = std::filesystem::file_size(
                file);
                std::string content(content_size, '\0');
                std::ifstream(file).read(content.data(), content_size);
                scheduler.Exchange(std::move(file), std::move(content));
            }
        }
    }

    auto Validate(std::string&& input, std::string&& outdir, Shader shader, std
    ::size_t threads) -> void
    {
        const std::filesystem::directory_iterator files(input, std::filesystem
        ::directory_options::follow_directory_symlink);
        Scheduler scheduler(std::forward<std::string>(outdir), shader, threads)
        ;
        for(const std::filesystem::directory_entry& a : files)
        {
            std::string file = Symlink(a.path());
            if(file.ends_with(".selka"))
            {
                const std::size_t content_size = std::filesystem::file_size(
                file);
                std::string content(content_size, '\0');
                std::ifstream(file).read(content.data(), content_size);
                scheduler.Exchange(std::move(file), std::move(content));
            }
        }
    }
}