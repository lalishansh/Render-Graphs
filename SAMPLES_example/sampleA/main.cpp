#include <fmt/core.h>

#include <iostream>

#include "version.h"

#if _WIN32
#include <Windows.h>
#undef min
#undef max
#endif

int
#if _WIN32
    WINAPI
    WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else
    main(int __argc, const char *__argv[])
#endif 
{
    fmt::print("Hello, World! from VERSION {}\n",
                HelloWorldProject_VERSION_STRING);
    std::cin.ignore();
    return 0;
}
