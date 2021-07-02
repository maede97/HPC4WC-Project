#include <HPC4WC/io.h>

namespace HPC4WC {

void IO::write(std::ostream& out, const Field& f, Field::const_idx_t& k) {
    for (Field::idx_t i = 0; i < f.num_i(); i++) {
        for (Field::idx_t j = 0; j < f.num_j(); j++) {
            out << f(i, j, k) << " ";
        }
        out << std::endl;
    }
}

void IO::write(std::ostream& out, const Field& f) {
    for (Field::idx_t k = 0; k < f.num_k(); k++) {
        write(out, f, k);
    }
}

}  // namespace HPC4WC