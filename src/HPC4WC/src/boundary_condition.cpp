#include <HPC4WC/boundary_condition.h>

namespace HPC4WC {

void PeriodicBoundaryConditions::apply(Field& field) {
    Field::const_idx_t ni = field.num_i();
    Field::const_idx_t nj = field.num_j();
    Field::const_idx_t num_halo = field.num_halo();
    for (Field::idx_t k = 0; k < field.num_k(); k++) {
        // copy top to bottom halo
        for (Field::idx_t i = 0; i < num_halo; i++) {
            for (Field::idx_t j = 0; j < field.num_j(); j++) {
                field(ni + i, j, k) = field(i, j, k);
            }
        }

        // copy bottom to top halo
        for (Field::idx_t i = 0; i < num_halo; i++) {
            for (Field::idx_t j = 0; j < field.num_j(); j++) {
                field(0 - num_halo + i, j, k) = field(ni - num_halo + i, j, k);
            }
        }

        // copy left to right halo
        for (Field::idx_t i = -num_halo; i < ni + num_halo; i++) {
            for (Field::idx_t j = 0; j < num_halo; j++) {
                field(i, j + nj, k) = field(i, j, k);
            }
        }

        // copy right to left halo
        for (Field::idx_t i = -num_halo; i < ni + num_halo; i++) {
            for (Field::idx_t j = 0; j < num_halo; j++) {
                field(i, 0 - num_halo + j, k) = field(i, nj - num_halo + j, k);
            }
        }
    }
}

}  // namespace HPC4WC