#include <HPC4WC/autotuner.h>
#include <HPC4WC/io.h>

#include <iostream>

int main(int argc, char* argv[]) {
    using namespace HPC4WC;

    // POC: only 1 iteration. increase this.
    AutoTuner autotuner("diffusion2d", "--ni=128 --nj=128 --nk=128 --num-iterations=1024 --block-i=false --block-j=false", 1);

    autotuner.add_range_argument("openmp-num-threads", 1, 6);

    autotuner.search();

    return 0;
}
