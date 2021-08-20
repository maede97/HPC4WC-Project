import subprocess
import os

user = "class155"

sizes = [2,4,8,16,32,64,128]

for i in sizes:
    for j in sizes:
        curr = "#pragma once\nnamespace HPC4WC {\n#define OPENMP_NUM_THREADS 1\n#define BLOCK_SIZE_I "
        curr = curr + str(i) + "\n#define BLOCK_SIZE_J " + str(j) + "\n}  // namespace HPC4WC"

        # Write config header
        with open(f"/users/{user}/HPC4WC-Project/src/HPC4WC/include/HPC4WC/config.h", "w") as wr:
            wr.write(curr)

        print(f"-blocking-size-i {i} -blocking-size-j {j}")
        # Run cmake
        os.chdir(f"/users/{user}/HPC4WC-Project/build")
        subprocess.run("cmake ..", shell=True, stderr=subprocess.DEVNULL, stdout=subprocess.DEVNULL)
        subprocess.run("make diffusion2d", shell=True, stderr=subprocess.DEVNULL, stdout=subprocess.DEVNULL)

        # Execute and measure
        os.chdir(f"/users/{user}/HPC4WC-Project/scripts/slurm")
        p = subprocess.run("bash block_ij.sh", shell=True, stderr=subprocess.DEVNULL, stdout=subprocess.PIPE)
        data = p.stdout.decode("ascii")

        print(data)