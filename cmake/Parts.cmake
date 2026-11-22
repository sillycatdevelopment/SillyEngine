# SillyEngine
# Build setup created by Claude (Anthropic AI) for SillyCatDevelopment.
#
# Finds the code in src/ and tests/ and turns it into targets. See the
# comment at the top of CMakeLists.txt for the rules.

include_guard(GLOBAL)

# Adds a folder's files to a target: *.cppm as C++ modules (importable by
# anything that links the target), *.cpp as ordinary sources.
function(_sillyengine_add_files target dir modules sources)
    if(modules)
        target_sources(${target} PUBLIC FILE_SET CXX_MODULES BASE_DIRS "${dir}" FILES ${modules})
    endif()
    if(sources)
        target_sources(${target} PRIVATE ${sources})
    endif()
    target_compile_features(${target} PUBLIC cxx_std_23)
    sillyengine_set_warnings(${target})
endfunction()

# sillyengine_add_parts(<src folder>)
# One target per folder in <src folder>: a library, or a program if the
# folder has a main.cpp directly inside it. Programs link every library.
# Afterwards SILLYENGINE_LIBRARIES (global property) lists the libraries.
function(sillyengine_add_parts src_dir)
    file(GLOB parts LIST_DIRECTORIES true CONFIGURE_DEPENDS "${src_dir}/*")
    set(libraries "")
    set(programs "")

    foreach(dir IN LISTS parts)
        if(NOT IS_DIRECTORY "${dir}")
            continue()
        endif()
        get_filename_component(name "${dir}" NAME)
        # Recorded even for empty parts: the first file you add to one
        # makes the next build re-run CMake.
        file(GLOB_RECURSE modules CONFIGURE_DEPENDS "${dir}/*.cppm")
        file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${dir}/*.cpp")
        if(NOT modules AND NOT sources)
            message(STATUS "src/${name}: no .cpp or .cppm files yet, skipped")
            continue()
        endif()

        if(EXISTS "${dir}/main.cpp")
            list(APPEND programs "${name}")
            set(_modules_${name} "${modules}")
            set(_sources_${name} "${sources}")
            set(_dir_${name} "${dir}")
        else()
            add_library(${name} STATIC)
            _sillyengine_add_files(${name} "${dir}" "${modules}" "${sources}")
            list(APPEND libraries "${name}")
            list(LENGTH modules module_count)
            list(LENGTH sources source_count)
            message(STATUS "src/${name}: library (${module_count} modules, ${source_count} sources)")
        endif()
    endforeach()

    # Programs last, so every library exists to link against.
    foreach(name IN LISTS programs)
        add_executable(${name})
        _sillyengine_add_files(${name} "${_dir_${name}}" "${_modules_${name}}" "${_sources_${name}}")
        if(libraries)
            target_link_libraries(${name} PRIVATE ${libraries})
        endif()
        message(STATUS "src/${name}: program -> build/<preset>/${name}")
    endforeach()

    set_property(GLOBAL PROPERTY SILLYENGINE_LIBRARIES "${libraries}")
endfunction()

# sillyengine_add_tests(<tests folder>)
# Every .cpp under <tests folder> goes into one GoogleTest program, "tests",
# linked with every library. GoogleTest's own main() runs them, so test
# files only contain TEST(...) blocks.
function(sillyengine_add_tests tests_dir)
    file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${tests_dir}/*.cpp")
    file(GLOB_RECURSE modules CONFIGURE_DEPENDS "${tests_dir}/*.cppm")
    if(NOT sources)
        message(STATUS "tests: no .cpp files yet, skipped")
        return()
    endif()

    include(FetchContent)
    FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        SYSTEM)
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        foreach(gtest_target gtest gtest_main)
            target_compile_options(${gtest_target} PRIVATE -Wno-unknown-warning-option -Wno-character-conversion)
        endforeach()
    endif()

    add_executable(tests)
    _sillyengine_add_files(tests "${tests_dir}" "${modules}" "${sources}")
    get_property(libraries GLOBAL PROPERTY SILLYENGINE_LIBRARIES)
    target_link_libraries(tests PRIVATE ${libraries} GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(tests DISCOVERY_TIMEOUT 30)
    list(LENGTH sources test_count)
    message(STATUS "tests: ${test_count} test files -> build/<preset>/tests")
endfunction()
