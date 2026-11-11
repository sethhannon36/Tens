cmake_minimum_required(VERSION 3.24)
project(Tens LANGUAGES C CXX)

# Force standard compliance
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_ttf REQUIRED)

# get all cpp files from src and subdirectories
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

# set source
add_executable(Tens ${SRC})

target_include_directories(Tens PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(Tens PRIVATE 
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
)