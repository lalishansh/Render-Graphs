#include "version.h"

#include <iostream>

#if _WIN32
#include <Windows.h>
#undef min
#undef max
#endif

#include <fmt/core.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <ThirdParty/header.hpp>

void test_warning_suppression();
int 
#if _WIN32
    WINAPI
    WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else
    main(int __argc, const char *__argv[])
#endif
{
    (void)__argc, (void)__argv;

    fmt::print("Hello, World! from VERSION {}\n",
                HelloWorldProject_VERSION_STRING);

    ThirdParty::say_hello<>();

    if (!glfwInit())
        return -1;
    auto wnd = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!wnd) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(wnd);
    while (glfwWindowShouldClose(wnd) == 0) {
        glfwSwapBuffers(wnd);
        glfwPollEvents();
    }

    std::cin.ignore();
    return 0;
}

#include <suppress-warnings/push>
#include <suppress-warnings/unused-variable>
#include <suppress-warnings/literal-conversion>
#include <suppress-warnings/macro-redefined>
void test_warning_suppression() {
    bool unused_var = true;
    int int_from_float = 1.1f;
}
#define REDEFINE_A_MACRO 1
#define REDEFINE_A_MACRO 2
#include <suppress-warnings/pop>