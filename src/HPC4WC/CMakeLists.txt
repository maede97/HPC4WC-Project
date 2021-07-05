cmake_minimum_required(VERSION 3.10)

project(HPC4WC)

file(
    GLOB
    SOURCE #
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" #
)

file(
    GLOB
    HEADER #
    "${CMAKE_CURRENT_SOURCE_DIR}/include/HPC4WC/*.h" #
)

find_package(OpenMP REQUIRED)
find_package(MPI REQUIRED)

add_library(${PROJECT_NAME} STATIC ${SOURCE} ${HEADER})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} 
    PUBLIC OpenMP::OpenMP_CXX
    PUBLIC MPI::MPI_CXX
    PUBLIC eigen
)
