#define BOOST_TEST_MODULE HelloWorldTests
#include <boost/test/included/unit_test.hpp>
#include <fmt/core.h>
#include <version.h>

#include <main.hpp>

BOOST_AUTO_TEST_CASE(hello_world_test) {
    std::string output = fmt::format("{}.{}.{}",
                                     HelloWorldProject_VERSION_MAJOR,
                                     HelloWorldProject_VERSION_MINOR,
                                     HelloWorldProject_VERSION_PATCH);
    LIB_example::say_hello();
    BOOST_TEST(output == HelloWorldProject_VERSION_STRING);
}
