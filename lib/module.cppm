module;

#ifndef USE_PCH
#include <string>
#endif

export module some_module;

namespace some
{
    export std::string some_string();
}