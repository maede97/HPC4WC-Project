import subprocess
import os
config = """#pragma once
namespace HPC4WC {
#define OPENMP_NUM_THREADS 1
#define BLOCK_SIZE_I {}
#define BLOCK_SIZE_J {}
}  // namespace HPC4WC
"""

sizes = [2,4,8,16,32,64,128]

for i in sizes:
    for j in sizes:
        curr = config.format(i,j)

        # Write config header
        with open("~/HPC4WC-Project/src/HPC4WC/include/HPC4WC/config.h", "w") as wr:
            wr.write(curr)

        print(f"-blocking-size-i {i} -blocking-size-j {j}")
        # Run cmake
        os.chdir("~/HPC4WC-Project/build")
        subprocess.run("cmake ..", shell=True, stderr=subprocess.DEVNULL, stdout=subprocess.DEVNULL)
        subprocess.run("make diffusion2d", shell=True, stderr=subprocess.DEVNULL, stdout=subprocess.DEVNULL)

        # Execute and measure
        os.chdir("~/HPC4WC-Project/build/src/executables")
        p = subprocess.run("./diffusion2d", shell=True, stderr=subprocess.DEVNULL, stdout=subprocess.PIPE)
        data = p.stdout

        print(data)