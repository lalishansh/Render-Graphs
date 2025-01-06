CMAKE_MINIMUM_REQUIRED(VERSION 3.21)

# add example target
# param: 
#   example_dir - example target directory, same as example name
FUNCTION(BUILD_EXAMPLE example_dir)
    IF (NOT EXISTS ${example_dir})
        MESSAGE(FATAL_ERROR "Example Dir: \"${example_dir}\" does not exist")
    ENDIF ()
    GET_FILENAME_COMPONENT(example_target "${example_dir}" NAME)

    IF (TARGET ${example_target})
        MESSAGE(WARNING "Example ${example_target} already exists, skipping BUILD_EXAMPLE step for this target")
        RETURN()
    ELSEIF (EXISTS ${example_dir}/CMakeLists.txt)
        MESSAGE(WARNING
                "Example ${example_target} has a CMakeLists.txt file, using add_subdirectory instead of BUILD_EXAMPLE")
        ADD_SUBDIRECTORY(${example_dir})
        RETURN()
    ENDIF ()

    MESSAGE(STATUS "Building example ${example_target} in ${example_dir}")
    FILE(GLOB_RECURSE example_src_files
            # header files
            "${example_dir}/**.h"
            "${example_dir}/**.hh"
            "${example_dir}/**.hpp"
            "${example_dir}/**.hxx"
            "${example_dir}/**.ixx" # Cpp20
            # source files
            "${example_dir}/**.c"
            "${example_dir}/**.cc"
            "${example_dir}/**.cpp"
            "${example_dir}/**.cxx"
            "${example_dir}/**.cppm" # Cpp20
        )

    # remove unit tests from the example source files
    SET(example_unit_tests_src_files)
    IF (EXISTS ${example_dir}/unit_tests.cpp)
        list(APPEND example_unit_tests_src_files ${example_dir}/unit_tests.cpp)
    ENDIF ()
    IF (EXISTS ${example_dir}/tests)
        FILE(GLOB_RECURSE from_tests_dir
                "${example_dir}/tests/**.h"
                "${example_dir}/tests/**.hh"
                "${example_dir}/tests/**.hpp"
                "${example_dir}/tests/**.hxx"
                "${example_dir}/tests/**.ixx" # Cpp20
                "${example_dir}/tests/**.c"
                "${example_dir}/tests/**.cc"
                "${example_dir}/tests/**.cpp"
                "${example_dir}/tests/**.cxx"
                "${example_dir}/tests/**.cppm" # Cpp20
            )
        LIST(APPEND example_unit_tests_src_files ${from_tests_dir})
    ENDIF ()
    LIST(REMOVE_ITEM example_src_files ${example_unit_tests_src_files})
    
    IF (WIN32)
        ADD_EXECUTABLE(${example_target} WIN32 ${example_src_files})
    ELSE ()
		ADD_EXECUTABLE(${example_target} ${example_src_files})
    ENDIF ()

    SET_TARGET_PROPERTIES(${example_target}
        PROPERTIES
            SOURCE_DIR ${example_dir}
        )

    TARGET_INCLUDE_DIRECTORIES(${example_target} 
        PRIVATE
            ${example_dir}/
            ${example_dir}/src/
        PUBLIC
            ${GENERATED_SOURCE_FILES_DIR}
        )
    
    TARGET_COMPILE_OPTIONS(${example_target}
        PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:/WX /W4>
            $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Wconversion>
            $<$<CXX_COMPILER_ID:GNU>:-fmodules-ts>
        )
    TARGET_COMPILE_DEFINITIONS(${example_target}
        PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>
        )
    TARGET_LINK_LIBRARIES(${example_target}
        PRIVATE
            ${REAL_LIB_TARGET}
        )
    
    # from ~vendor dir
    TARGET_INCLUDE_DIRECTORIES(${example_target} PRIVATE
            ${CMAKE_SOURCE_DIR}/~vendor/include
        )
    
    # VcPkg packages
    IF (NOT TARGET fmt::fmt)
        FIND_PACKAGE(fmt CONFIG REQUIRED)
    ENDIF ()
    TARGET_LINK_LIBRARIES(${example_target}
        PRIVATE
            fmt::fmt
        )

    # tests target
    ADD_TESTS_TARGET_FOR_TARGET_FROM_SRC_FILES(
        ${example_target} ${example_target}_test ${example_unit_tests_src_files}
            INCLUDE_DIRECTORIES
            COMPILE_DEFINITIONS
            COMPILE_OPTIONS
            LINK_LIBRARIES
            LINK_DIRECTORIES
        )

    # Install the example to the install directory
    INSTALL_TARGET_AND_ITS_DEPENDENCIES(${example_target} "./bin")
ENDFUNCTION()

# for every example in the examples directory
# add a test target and an example target
FILE(GLOB example_dirs ${CMAKE_CURRENT_SOURCE_DIR}/*)
FOREACH (example_dir IN LISTS example_dirs)
    IF (IS_DIRECTORY ${example_dir})
        BUILD_EXAMPLE(${example_dir})
    ENDIF ()
ENDFOREACH ()
