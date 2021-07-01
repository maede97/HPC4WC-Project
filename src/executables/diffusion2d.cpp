#include <HPC4WC/boundary_condition.h>
#include <HPC4WC/diffusion.h>
#include <HPC4WC/field.h>
#include <HPC4WC/initial_condition.h>
#include <HPC4WC/io.h>

#include <Eigen/Core>
#include <fstream>

int main(int argc, char const* argv[]) {
    using namespace HPC4WC;

    Field f(128, 128, 64, 2);
    Field tmp(128, 128, 64, 2);

    CubeInitialCondition::apply(f);

    std::ofstream initial_of("initial.mat");
    IO::write(initial_of, f, 32);

    for (int t = 0; t < 0; t++) {
        PeriodicBoundaryConditions::apply(f);
        Diffusion::apply(f, tmp, 1. / 32.);

        // copy over tmp to f
        f.setFrom(tmp);
    }

    std::ofstream final_of("final.mat");
    IO::write(final_of, f, 32);

    return 0;
}
