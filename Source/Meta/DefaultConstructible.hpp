#pragma once

namespace Selka::Meta
{
    template<class T> concept DefaultConstructible = __is_constructible(T);
}