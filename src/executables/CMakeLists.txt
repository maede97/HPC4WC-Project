cmake_minimum_required(VERSION 3.10)

project(executables)

add_executable(diffusion2d diffusion2d.cpp)
target_link_libraries(diffusion2d eigen HPC4WC)
target_include_directories(diffusion2d PUBLIC HPC4WC)

add_executable(autotune_search autotune_search.cpp)
target_link_libraries(autotune_search eigen HPC4WC)
target_include_directories(autotune_search PUBLIC HPC4WC)

if(${MPI_FOUND})
    add_executable(mpi_diffusion mpi_diffusion.cpp)
    target_link_libraries(mpi_diffusion eigen HPC4WC)
    target_include_directories(mpi_diffusion PUBLIC HPC4WC)
endif(${MPI_FOUND})

add_executable(experiment_openmp_k experiment_openmp_k.cpp)
target_link_libraries(experiment_openmp_k eigen HPC4WC)
target_include_directories(experiment_openmp_k PUBLIC HPC4WC)
add_dependencies(experiment_openmp_k diffusion2d)