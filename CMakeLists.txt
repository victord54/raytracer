cmake_minimum_required(VERSION 3.10)

project(raytracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add openMP
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

file(GLOB_RECURSE SOURCES "src/*.cpp")
file (GLOB_RECURSE HEADERS "src/*.hpp")

# Use gprof for profiling only in debug mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
endif()

# Add stb library
# add_library(stb INTERFACE)
# target_include_directories(stb INTERFACE "lib/stb")

add_executable(raytracer ${SOURCES} ${HEADERS})
# target_link_libraries(raytracer stb)