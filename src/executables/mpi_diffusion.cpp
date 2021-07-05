#include <HPC4WC/boundary_condition.h>
#include <HPC4WC/diffusion.h>
#include <HPC4WC/field.h>
#include <HPC4WC/initial_condition.h>
#include <HPC4WC/io.h>
#include <HPC4WC/timer.h>
#include <HPC4WC/partitioner.h>

#include <Eigen/Core>
#include <fstream>

int main(int argc, char* argv[]) {
    using namespace HPC4WC;

    Partitioner::init(argc, argv);
    Partitioner p(128, 128, 64, 2);

    auto f = p.getField();
    if (p.rank() == 0)
    {
        auto global_f = p.getGlobalField();
        CubeInitialCondition::apply(*global_f.get());
        std::ofstream initial_of("initial.mat");
        IO::write(initial_of, *global_f.get(), 32);
    }

    p.scatter();

    auto timer = Timer();

    for (int t = 0; t < 10; t++) {
        p.haloExchange();
        PeriodicBoundaryConditions::apply(*f.get());
        Diffusion::apply(*f.get(), 1. / 32.);
    }

    double time = timer.timeElapsed();
    std::cout << "Time elapsed: " << time << std::endl;

    p.gather();

    if (p.rank() == 0) {
        auto global_f = p.getGlobalField();
        std::ofstream final_of("final.mat");
        IO::write(final_of, *global_f.get(), 32);
    }

    Partitioner::finalize();

    return 0;
}
