cmake_minimum_required(VERSION 3.19)
project(DirectXTests)
set(CMAKE_CXX_STANDARD 14)



set(UTILS_SOURCE
        lib/pch.cpp

        lib/error_handling/FileHandling.cpp
        lib/error_handling/WindowsErrorHandling.cpp

        lib/graphics/D3DInit.cpp
        lib/graphics/Shader.cpp

        lib/platform/Window.cpp)
add_library(lib STATIC ${UTILS_SOURCE})
target_include_directories(lib PUBLIC lib/include)



add_executable(01ClearScreen WIN32 01ClearScreen/WinMain.cpp)
target_include_directories(01ClearScreen PRIVATE lib/include)
add_dependencies(01ClearScreen lib)
target_link_libraries(01ClearScreen lib)

add_executable(02Triangle WIN32 lib/graphics/VertexBuffer.cpp 02Triangle/WinMain.cpp)
target_include_directories(02Triangle PRIVATE lib/include)
add_dependencies(02Triangle lib)
target_link_libraries(02Triangle lib)
add_custom_target(copy_assets_02
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/02Triangle/assets
        ${CMAKE_CURRENT_BINARY_DIR}/assets
        )
add_dependencies(02Triangle copy_assets_02)
