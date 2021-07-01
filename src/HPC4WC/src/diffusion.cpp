#include <HPC4WC/diffusion.h>
#include <omp.h>
namespace HPC4WC {

void Diffusion::apply(const Field& f_in, Field& f_out, const double& alpha) {
    const double a1 = -1. * alpha;
    const double a2 = -2. * alpha;
    const double a8 = 8. * alpha;
    const double a20 = 1. - 20. * alpha;

#pragma omp parallel for shared(f_in, f_out) firstprivate(a1, a2, a8, a20)
    for (Field::idx_t k = 0; k < f_in.num_k(); k++) {
        for (Field::idx_t i = 0; i < f_in.num_i(); i++) {
            for (Field::idx_t j = 0; j < f_in.num_j(); j++) {
                f_out(i, j, k) = a1 * f_in(i, j - 2, k) + a2 * f_in(i - 1, j - 1, k) + a8 * f_in(i, j - 1, k) + a2 * f_in(i + 1, j - 1, k) +
                                 a1 * f_in(i - 2, j, k) + a8 * f_in(i - 1, j, k) + a20 * f_in(i, j, k) + a8 * f_in(i + 1, j, k) + a1 * f_in(i + 2, j, k) +
                                 a2 * f_in(i - 1, j + 1, k) + a8 * f_in(i, j + 1, k) + a2 * f_in(i + 1, j + 1, k) + a1 * f_in(i, j + 2, k);
            }
        }
    }
}

}  // namespace HPC4WC