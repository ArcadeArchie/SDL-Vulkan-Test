cmake_minimum_required(VERSION 3.25)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_C_STANDARD 17)   
set(CMAKE_C_STANDARD_REQUIRED ON)

project(somethingVulkanSDL VERSION 0.1.0)
enable_language(C)
enable_language(CXX)
#include(CTest)
#enable_testing()
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(Vulkan REQUIRED vulkan)

include_directories( 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SDL2_INCLUDE_DIRS}
    ${Vulkan_INCLUDE_DIRS}
)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "src/*.cpp")
add_executable(somethingVulkanSDL ${sources})

target_compile_options(somethingVulkanSDL PUBLIC -O0)

target_link_libraries(
    somethingVulkanSDL
    ${SDL2_LIBRARIES}
    ${Vulkan_LIBRARIES}
)


#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)
