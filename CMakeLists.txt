cmake_minimum_required(VERSION 3.10)
project(CustroEngine)

set(CMAKE_CXX_STANDARD 17)

include_directories(libs/glfw/include)
include_directories(libs/glad/include)
include_directories(CustroEngine/src)

file(GLOB_RECURSE ALL_FILES
        "CustroEngine/src/*"
)

add_executable(CustroEngine
        ${ALL_FILES}
        libs/glad/src/glad.c
)

target_link_libraries(CustroEngine
        ${CMAKE_SOURCE_DIR}/libs/glfw/lib/glfw3.lib
        opengl32
        gdi32
)

target_include_directories(CustroEngine PRIVATE libs)