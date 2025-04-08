#ifndef USE_PCH
#include <string>
#include <iostream>
#endif

import some_module;

int main()
{
    std::cout << some::some_string() << "\n";

    return 0;
}