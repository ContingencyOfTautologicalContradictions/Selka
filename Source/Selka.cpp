#include "Core/Symlink.hpp"
#include "Core/Validator.hpp"
#include <iostream>
#include <filesystem>

int main(int argc, char** argv)
{
    if(argc < 4 or argc > 5)
    {
        std::cerr << "Mismatch of arguments, please consult "
        "https://github.com/ContingencyOfTautologicalContradictions/Selka/blob"
        "/main/README.md#usage";
        std::abort();
    }
    std::string input = Selka::Symlink(argv[1]);
    if(not std::filesystem::is_directory(input))
    {
        std::cerr << "The given input directory '" << input << "' ain't "
        "pointing to an existing directory";
        std::abort();
    }
    std::string outdir = Selka::Symlink(argv[2]);
    if(not outdir.ends_with('/'))
        outdir.append(1z, '/');
    if(not std::filesystem::is_directory(outdir))
    {
        std::cerr << "The given output directory '" << outdir << "' ain't "
        "pointing to an existing directory";
        std::abort();
    }
    argc == 5 ? Selka::Validator::Validate(std::move(input), std::move(outdir),
    Selka::ShaderLanguage(argv[3]), std::stoull(std::string(argv[4]))) : Selka
    ::Validator::Validate(std::move(input), std::move(outdir), Selka::
    ShaderLanguage(argv[3]));
}