
cmake_minimum_required(VERSION 3.20)

project(MembraneSimulator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(membrane_simulator
    src/main.cpp
    src/physics/Membrane.cpp
    src/physics/WaveSolver.cpp
)

target_include_directories(membrane_simulator PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/physics
)

target_link_libraries(membrane_simulator PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)
