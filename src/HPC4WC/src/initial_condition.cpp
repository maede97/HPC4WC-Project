#include <HPC4WC/initial_condition.h>

void HPC4WC::CubeInitialCondition::apply(Field& field) {
    using const_idx_t = Field::const_idx_t;
    const_idx_t i_1third = field.num_i() / 3;
    const_idx_t i_2third = 2 * field.num_i() / 3;
    const_idx_t j_1third = field.num_j() / 3;
    const_idx_t j_2third = 2 * field.num_j() / 3;
    const_idx_t k_1third = field.num_k() / 3;
    const_idx_t k_2third = 2 * field.num_k() / 3;

    for (Field::idx_t i = i_1third; i < i_2third; i++) {
        for (Field::idx_t j = j_1third; j < j_2third; j++) {
            for (Field::idx_t k = k_1third; k < k_2third; k++) {
                field(i, j, k) = 1.;
            }
        }
    }
}