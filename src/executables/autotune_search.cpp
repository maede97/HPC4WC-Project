#include <HPC4WC/autotuner.h>
#include <HPC4WC/io.h>

#include <iostream>

int main(int argc, char* argv[]) {
    using namespace HPC4WC;
    ArgsParser argsParser(argc, argv, false);

    std::string executable = "diffusion2d";
    std::string more_args = "";
    argsParser.add_argument(executable, "executable", "The file to execute and measure time for.");
    argsParser.add_argument(more_args, "exe-args", "More arguments passed to the executable.");

    if (argsParser.help()) {
        argsParser.help(std::cout);
        return 0;
    }

    // Do not add .exe on windows, it will be found. This version now works on windows and linux!
    AutoTuner autotuner(executable.c_str(), more_args.c_str());

    autotuner.add_range_argument("openmp-num-threads", 1, 4);

    autotuner.search();

    return 0;
}
