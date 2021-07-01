#include <HPC4WC/config.h>
#include <HPC4WC/diffusion.h>
#include <omp.h>

namespace HPC4WC {

void Diffusion::apply(Field& f, Field& tmp, const double& alpha) {
    const double a1 = -1. * alpha;
    const double a2 = -2. * alpha;
    const double a8 = 8. * alpha;
    const double a20 = 1. - 20. * alpha;

#ifdef USE_OPENMP_ON_K
#pragma omp parallel for shared(f, tmp) firstprivate(a1, a2, a8, a20)
#endif
    for (Field::idx_t k = 0; k < f.num_k(); k++) {
        for (Field::idx_t i = 0; i < f.num_i(); i++) {
            for (Field::idx_t j = 0; j < f.num_j(); j++) {
                tmp(i, j, k) = a1 * f(i, j - 2, k) + a2 * f(i - 1, j - 1, k) + a8 * f(i, j - 1, k) + a2 * f(i + 1, j - 1, k) +
                                 a1 * f(i - 2, j, k) + a8 * f(i - 1, j, k) + a20 * f(i, j, k) + a8 * f(i + 1, j, k) + a1 * f(i + 2, j, k) +
                                 a2 * f(i - 1, j + 1, k) + a8 * f(i, j + 1, k) + a2 * f(i + 1, j + 1, k) + a1 * f(i, j + 2, k);
            }
        }
    }

    // copy back tmp to f
    f.setFrom(tmp);
}

}  // namespace HPC4WC