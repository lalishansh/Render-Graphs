#include <main.hpp>

#include <stdio.h>
#include <source_location>

#include <fmt/core.h>

void LIB_example::say_hello() {
    printf("Hello, world! from %s\n",
           __FILE__);
}
