#pragma once
#include <HPC4WC/field.h>

namespace HPC4WC {

/**
 * @brief Configuration class for blocking, OMP, MPI.
 */
class Config {
public:
    //static bool USE_OPENMP_ON_K;
    static Field::idx_t OPENMP_NUM_THREADS;

    static Field::idx_t BLOCK_SIZE_I;
    static Field::idx_t BLOCK_SIZE_J;

    static bool BLOCK_I;
    static bool BLOCK_J;
};
}  // namespace HPC4WC
