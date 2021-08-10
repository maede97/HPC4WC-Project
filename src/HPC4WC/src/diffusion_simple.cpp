#include <HPC4WC/config.h>
#include <HPC4WC/diffusion.h>

namespace HPC4WC {

// apply laplacian to f_in and write into f_out.
// start at (offset_i, offset_j) (without halo points there!)
void laplacian(const Field& f_in, Field& f_out, Field::const_idx_t& offset_i = 0, Field::const_idx_t& offset_j = 0) {
    // TODO: perform blocking based on f_out size?
    // TODO: size checks on the fields
    for (Field::idx_t k = 0; k < f_in.num_k(); k++) {
        for (Field::idx_t i_out = f_out.num_halo(); i_out < f_out.num_i() + f_out.num_halo(); i_out++) {
            for (Field::idx_t j_out = f_out.num_halo(); j_out < f_out.num_j() + f_out.num_halo(); j_out++) {
                f_out(i_out, j_out, k) = -4. * f_in(i_out + offset_i, j_out + offset_j, k) + f_in(i_out - 1 + offset_i, j_out + offset_j, k) +
                                         f_in(i_out + 1 + offset_i, j_out + offset_j, k) + f_in(i_out + offset_i, j_out - 1 + offset_j, k) +
                                         f_in(i_out + offset_i, j_out + 1 + offset_j, k);
            }
        }
    }
}

void time_integration(const Field& f_in, Field& f_out, const double& alpha) {
    // TODO: check field size
    for (Field::idx_t k = 0; k < f_in.num_k(); k++) {
        for (Field::idx_t i_out = f_out.num_halo(); i_out < f_out.num_i() + f_out.num_halo(); i_out++) {
            for (Field::idx_t j_out = f_out.num_halo(); j_out < f_out.num_j() + f_out.num_halo(); j_out++) {
                f_out(i_out, j_out, k) = f_out(i_out, j_out, k) - alpha * f_in(i_out, j_out, k);
            }
        }
    }
}

void copy_to(const Field& f_in, Field& f_out, Field::const_idx_t& offset_i = 0, Field::const_idx_t& offset_j = 0) {
    for (Field::idx_t k = 0; k < f_in.num_k(); k++) {
        for (Field::idx_t i = f_out.num_halo(); i < f_in.num_i() + f_in.num_halo(); i++) {
            for (Field::idx_t j = f_out.num_halo(); j < f_in.num_j() + f_in.num_halo(); j++) {
                f_out(i + offset_i, j + offset_j, k) = f_in(i, j, k);
            }
        }
    }
}

void SimpleDiffusion::apply(Field& f, const double& alpha) {
    //TODO: must check that block_size divides f size!
    // otherwise error.
    Field::idx_t block_i, block_j;

    if (Config::BLOCK_I && Config::BLOCK_J) {
        block_i = Config::BLOCK_SIZE_I;
        block_j = Config::BLOCK_SIZE_J;
    } else if (Config::BLOCK_I) {
        block_i = Config::BLOCK_SIZE_I;
        block_j = f.num_j();
    } else if (Config::BLOCK_J) {
        block_i = f.num_i();
        block_j = Config::BLOCK_SIZE_J;
    } else {
        block_i = f.num_i();
        block_j = f.num_j();
    }

    Field tmp1 = Field(block_i + 2, block_j + 2, f.num_k(), f.num_halo());
    Field tmp2 = Field(block_i, block_j, f.num_k(), f.num_halo());

    Field tmp3 = Field(f.num_i(), f.num_j(), f.num_k(), f.num_halo());

    for (Field::idx_t block_i_start = 0; block_i_start < f.num_i(); block_i_start += block_i) {
        for (Field::idx_t block_j_start = 0; block_j_start < f.num_j(); block_j_start += block_j) {
            laplacian(f, tmp1, block_i_start - 1, block_j_start - 1);
            laplacian(tmp1, tmp2, 1, 1);

            copy_to(tmp2, tmp3, block_i_start, block_j_start);
        }
    }

    // erst ganz am schluss
    time_integration(tmp3, f, alpha);
}

}  // namespace HPC4WC