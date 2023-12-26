#include "FunctionDecl.hpp"

namespace Selka::Spell
{
    auto FunctionDecl::Shade(std::string& source, ShaderKind& shader) const -> void
    {

    }

    void from_json(const nlohmann::json& data, FunctionDecl& fd)
    {
        fd.name = Json::Field<std::string>(data, "name");
        fd.type = Json::Field<Type>(data, "type");
    }
}