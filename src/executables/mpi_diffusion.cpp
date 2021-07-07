#include <HPC4WC/boundary_condition.h>
#include <HPC4WC/diffusion.h>
#include <HPC4WC/field.h>
#include <HPC4WC/initial_condition.h>
#include <HPC4WC/io.h>
#include <HPC4WC/partitioner.h>
#include <HPC4WC/timer.h>

#include <Eigen/Core>
#include <fstream>

// Argsparser
#include <flags.h>
#ifdef _WIN32
#define PATH_CHAR "\\"
#else
#define PATH_CHAR "/"
#endif
#define PARSE_EXE_NAME(name) \
    std::string(name).substr(std::string(name).find_last_of(PATH_CHAR) + 1, std::string(name).size() - std::string(name).find_last_of(PATH_CHAR) - 1)


int main(int argc, char* argv[]) {
    using namespace HPC4WC;

    const flags::args args(argc, argv);
    Field::const_idx_t ni = args.get<Field::idx_t>("ni", 64);
    Field::const_idx_t nj = args.get<Field::idx_t>("nj", 64);
    Field::const_idx_t nk = args.get<Field::idx_t>("nk", 64);
    Field::const_idx_t num_halo = args.get<Field::idx_t>("num_halo", 2);
    Field::const_idx_t num_timesteps = args.get<Field::idx_t>("iterations", 100);
    bool showHelp = args.get<bool>("help", false);


    Partitioner::init(argc, argv);
    Partitioner p(ni, nj, nk, num_halo);

    if (showHelp) {
        if (p.rank() == 0) {
            std::cout << PARSE_EXE_NAME(argv[0]) << " [--help] [--ni=64] [--nj=64] [--nk=64] [--num_halo=2] [--iterations=100]" << std::endl;
            std::cout << "    Optional arguments:" << std::endl << "    help: Shows this help and exits." << std::endl;
            std::cout << "    ni: Number of interiour points in i direction." << std::endl;
            std::cout << "    nj: Number of interiour points in j direction." << std::endl;
            std::cout << "    nk: Number of interiour points in k direction." << std::endl;
            std::cout << "    num_halo: Number of halo points in i and j direction." << std::endl;
            std::cout << "    iterations: Number of diffusion iterations." << std::endl;
        }
        Partitioner::finalize();
        return 0;
    }

    if (p.rank() == 0) {
        FieldSPtr global_f = p.getGlobalField();
        CubeInitialCondition::apply(*global_f.get());
        std::ofstream initial_of("initial.txt");
        IO::write(initial_of, *global_f.get(), nk / 2);
    }

    p.scatter();

    auto timer = Timer();
    for (Field::idx_t t = 0; t < num_timesteps; t++) {
        p.applyPeriodicBoundaryConditions();
        Diffusion::apply(*p.getField().get(), 1. / 32.);
    }

    double time = timer.timeElapsed();
    std::cout << "Rank: " << p.rank() << ", Time elapsed: " << time << std::endl;

    p.gather();

    if (p.rank() == 0) {
        FieldSPtr global_f = p.getGlobalField();
        std::ofstream final_of("final.txt");
        IO::write(final_of, *global_f.get(), nk / 2);
    }

    Partitioner::finalize();

    return 0;
}
