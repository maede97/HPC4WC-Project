#include <HPC4WC/initial_condition.h>

void HPC4WC::CubeInitialCondition::apply(Field& field) {
    using const_idx_t = Field::const_idx_t;
    const_idx_t num_halo = field.num_halo();
    const_idx_t i_1third = field.num_i() / 3 + num_halo;
    const_idx_t i_2third = 2 * field.num_i() / 3 + num_halo; 
    const_idx_t j_1third = field.num_j() / 3 + num_halo;
    const_idx_t j_2third = 2 * field.num_j() / 3 + num_halo;
    const_idx_t k_1third = field.num_k() / 3 + num_halo;
    const_idx_t k_2third = 2 * field.num_k() / 3 + num_halo;

    for (Field::idx_t i = i_1third; i < i_2third; i++) {
        for (Field::idx_t j = j_1third; j < j_2third; j++) {
            for (Field::idx_t k = k_1third; k < k_2third; k++) {
                field(i, j, k) = 1.;
            }
        }
    }
}

void HPC4WC::DiagonalInitialCondition::apply(Field& field) {
    using const_idx_t = Field::const_idx_t;
    const_idx_t num_halo = field.num_halo();
    for (Field::idx_t i = 0; i < field.num_i(); i++) {
        for (Field::idx_t j = 0; j < field.num_j(); j++) {
            for (Field::idx_t k = 0; k < field.num_k(); k++) {
                if ((i + j) % 4 == 0) {
                    field(i+num_halo, j+num_halo, k) = 1.;
                }
            }
        }
    }
}