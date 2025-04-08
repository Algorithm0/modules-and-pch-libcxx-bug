module;

#ifndef USE_PCH
#include <string>
#ifdef USE_STD_FORMAT
#include <format>
#endif
#endif

module some_module;

namespace some
{
    std::string some_string()
    {
        #ifdef USE_STD_FORMAT
        constexpr int s1 = 1;
        constexpr std::string_view s2 = "STRING";
        return std::format("These {} lines are output ({}) using the std::format", s1, s2);
        #else
        return "some string";
        #endif
    }
}
