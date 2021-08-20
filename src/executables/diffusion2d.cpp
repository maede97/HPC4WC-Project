#include <HPC4WC/boundary_condition.h>
#include <HPC4WC/config.h>
#include <HPC4WC/diffusion.h>
#include <HPC4WC/field.h>
#include <HPC4WC/initial_condition.h>
#include <HPC4WC/io.h>
#include <HPC4WC/timer.h>

#include <Eigen/Core>
#include <fstream>

int main(int argc, char* argv[]) {
    using namespace HPC4WC;

    double total_time = 0.;

    Field::idx_t ni = 128, nj = 128, nk = 32, num_halo = 2, num_timesteps = 64;

    for(int i = 0; i < 4; i++) {
        Field f(ni, nj, nk, num_halo);

        CubeInitialCondition::apply(f);

        auto timer = Timer();

        for (int t = 0; t < num_timesteps; t++) {
            PeriodicBoundaryConditions::apply(f);
            SimpleDiffusion::apply(f, 1. / 32.);
        }

        double time = timer.timeElapsed();
        total_time += time;
    }

    std::cout << "Time elapsed: " << total_time / 4. << std::endl;

    return 0;
}
