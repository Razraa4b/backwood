cmake_minimum_required(VERSION 4.0)

project(Backwood)

file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE HEADERS *.hpp *.tpp *.inl)

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v0.1.36
)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
set(GLAD_API "gl=4.6" CACHE STRING "OpenGL API version")
set(GLAD_GENERATOR "c" CACHE STRING "Generator to use")
set(GLAD_SPEC "gl" CACHE STRING "Specification")
set(GLAD_NO_LOAD OFF CACHE BOOL "Disable adding the loader to the build")
set(GLAD_LOCAL OFF CACHE BOOL "Search for headers locally")
set(GLAD_REPRODUCIBLE OFF CACHE BOOL "Make build reproducible")
set(GLAD_MX OFF CACHE BOOL "Generate a header that supports multiple contexts")

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

FetchContent_MakeAvailable(glfw glad)

add_library(${PROJECT_NAME} 
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    glad
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${glfw_SOURCE_DIR}/include
    ${glad_SOURCE_DIR}/include
)
