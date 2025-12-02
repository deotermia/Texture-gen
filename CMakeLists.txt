cmake_minimum_required(VERSION 3.10)
project(texture_generator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Source files
set(SOURCES
        src/main.cpp
        src/core/texture_generator.cpp
        src/noise/perlin_noise.cpp
        src/noise/simplex_noise.cpp
        src/noise/noise_factory.cpp
        src/utils/color_gradient.cpp
        src/utils/image_writer.cpp
)

# Create executable
add_executable(texture_gen ${SOURCES})

# Include directories
target_include_directories(texture_gen PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

message(STATUS "Build target: texture_gen")