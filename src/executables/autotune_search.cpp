#include <HPC4WC/autotuner.h>
#include <iostream>

int main(int argc, char* argv[]) {
    using namespace HPC4WC;

    // Do not add .exe on windows, it will be found. This version now works on windows and linux!
    AutoTuner autotuner("diffusion2d");

    std::cout << autotuner.open_with_arguments("--openmp-num-threads=1") << std::endl;
    std::cout << autotuner.open_with_arguments("--openmp-num-threads=2") << std::endl;
    std::cout << autotuner.open_with_arguments("--openmp-num-threads=4") << std::endl;

    return 0;
}
