#include <HPC4WC/boundary_condition.h>

namespace HPC4WC {

void PeriodicBoundaryConditions::apply(Field& field) {
    Field::const_idx_t ni = field.num_i();
    Field::const_idx_t nj = field.num_j();
    Field::const_idx_t num_halo = field.num_halo();
    for (Field::idx_t k = 0; k < field.num_k(); k++) {
        // copy top to bottom halo
        for (Field::idx_t i = 0; i < num_halo; i++) {
            for (Field::idx_t j = num_halo; j < nj + num_halo; j++) {
                field(ni + i + num_halo, j, k) = field(i+num_halo, j, k);
            }
        }

        // copy bottom to top halo
        for (Field::idx_t i = 0; i < num_halo; i++) {
            for (Field::idx_t j = num_halo; j < nj + num_halo; j++) {
                field(i, j, k) = field(ni + i, j, k);
            }
        }

        // copy left to right halo
        for (Field::idx_t i = 0; i < ni + 2*num_halo; i++) {
            for (Field::idx_t j = 0; j < num_halo; j++) {
                field(i, j + nj + num_halo, k) = field(i, j+num_halo, k);
            }
        }

        // copy right to left halo
        for (Field::idx_t i = 0; i < ni + 2*num_halo; i++) {
            for (Field::idx_t j = 0; j < num_halo; j++) {
                field(i, j, k) = field(i, nj + j, k);
            }
        }
    }
}

}  // namespace HPC4WC