cmake_minimum_required(VERSION 3.10)

project(autotuner)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} eigen HPC4WC)
target_include_directories(${PROJECT_NAME} PUBLIC HPC4WC)