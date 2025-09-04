cmake_minimum_required(VERSION 4.0)

project(Backwood)

file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE HEADERS *.hpp *.tpp *.inl)

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
