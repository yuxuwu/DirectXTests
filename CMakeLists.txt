cmake_minimum_required(VERSION 3.19)
project(DirectXTests)

set(CMAKE_CXX_STANDARD 14)


set(UTILS_SOURCE
        utils/pch.cpp

        utils/error_handling/FileHandling.cpp
        utils/error_handling/WindowsErrorHandling.cpp

        utils/platform/Window.cpp)
add_library(utils STATIC ${UTILS_SOURCE})
target_include_directories(utils PUBLIC utils/include)



add_executable(01ClearScreen WIN32 01ClearScreen/D3DInit.cpp 01ClearScreen/WinMain.cpp)
target_include_directories(01ClearScreen PRIVATE utils/include)
add_dependencies(01ClearScreen utils)
target_link_libraries(01ClearScreen utils)



add_executable(02Triangle WIN32 02Triangle/D3DInit.cpp 02Triangle/WinMain.cpp)
target_include_directories(02Triangle PRIVATE utils/include)
add_dependencies(02Triangle utils)
target_link_libraries(02Triangle utils)
add_custom_target(copy_assets_02
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/02Triangle/assets
        ${CMAKE_CURRENT_BINARY_DIR}/assets
        )
add_dependencies(02Triangle copy_assets_02)
