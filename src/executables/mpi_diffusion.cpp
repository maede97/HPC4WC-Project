#include <HPC4WC/boundary_condition.h>
#include <HPC4WC/diffusion.h>
#include <HPC4WC/field.h>
#include <HPC4WC/initial_condition.h>
#include <HPC4WC/io.h>
#include <HPC4WC/partitioner.h>
#include <HPC4WC/timer.h>

#include <Eigen/Core>
#include <fstream>

int main(int argc, char* argv[]) {
    using namespace HPC4WC;

    Partitioner::init(argc, argv);

    Partitioner p(128, 128, 64, 2);

    if (p.rank() == 0) {
        FieldSPtr global_f = p.getGlobalField();
        CubeInitialCondition::apply(*global_f.get());
        std::ofstream initial_of("initial.txt");
        IO::write(initial_of, *global_f.get(), 32);
    }

    p.scatter();

    auto timer = Timer();
    for (int t = 0; t < 1024; t++) {
        p.applyPeriodicBoundaryConditions();
        Diffusion::apply(*p.getField().get(), 1. / 32.);
    }

    double time = timer.timeElapsed();
    std::cout << "Rank: " << p.rank() << ", Time elapsed : " << time << std::endl;

    p.gather();

    if (p.rank() == 0) {
        FieldSPtr global_f = p.getGlobalField();
        std::ofstream final_of("final.txt");
        IO::write(final_of, *global_f.get(), 32);
    }

    Partitioner::finalize();

    return 0;
}
