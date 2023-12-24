#pragma once
#define compute(x, y, z) static_assert(true, "selka.shading.compute " #x ':' #y ':' #z);
#define vertex static_assert(true, "selka.shading.vertex");
#define fragment static_assert(true, "selka.shading.fragment");

