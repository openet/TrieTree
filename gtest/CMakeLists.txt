cmake_minimum_required(VERSION 3.11)

set(GTEST_VERSION 1.8.0 CACHE STRING "Google test version")

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-${GTEST_VERSION})

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

enable_testing()

# Add test cpp file
add_executable(
    runUnitTests 
    main.cc 
    TrieTreeTest.cc)

# # Include directories
target_include_directories(
    gtest INTERFACE ${gtest_SOURCE_DIR}/include ${Source_Dir})

# # Link test executable against gtest & gtest_main
target_link_libraries(
    runUnitTests 
    gtest
    gtest_main)

include(GoogleTest)
gtest_discover_tests(runUnitTests)

