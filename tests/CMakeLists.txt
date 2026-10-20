find_package(GTest CONFIG QUIET)

# Fall back to downloading GoogleTest if it isn't installed
if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
    )
    FetchContent_MakeAvailable(googletest)
endif()

include(GoogleTest)

add_executable(tests
    smoke_test.cpp
)
target_link_libraries(tests PRIVATE kv_warnings GTest::gtest_main)

gtest_discover_tests(tests)
