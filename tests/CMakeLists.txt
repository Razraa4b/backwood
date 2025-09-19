cmake_minimum_required(VERSION 4.0)

project(BackwoodTests)

file(GLOB_RECURSE SOURCES *.cpp *.cc)

include(FetchContent)

# Install googletest repository
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For WindowBases: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Backwood
    GTest::gtest
    GTest::gmock
    glfw
    glad
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME tests
)
