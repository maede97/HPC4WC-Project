cmake_minimum_required(VERSION 3.10)

project(executables)

add_executable(diffusion2d diffusion2d.cpp)
target_link_libraries(diffusion2d eigen HPC4WC)
target_include_directories(diffusion2d PUBLIC HPC4WC)