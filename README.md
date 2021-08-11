# HPC4WC-Project
![Build](https://github.com/maede97/HPC4WC-Project/actions/workflows/build.yml/badge.svg)
![UnitTests](https://github.com/maede97/HPC4WC-Project/actions/workflows/unittests.yml/badge.svg)
![Documentation](https://github.com/maede97/HPC4WC-Project/actions/workflows/documentation.yml/badge.svg)

## Documentation
The documentation is built using doxygen and publicly available: [https://maede97.github.io/HPC4WC-Project](https://maede97.github.io/HPC4WC-Project)

## Unittests
Unittests are automatically built and run on Windows and Ubuntu, both in Release and Debug mode. See [folder tests](https://github.com/maede97/HPC4WC-Project/tree/master/tests).

## Piz Daint
Our code is designed that it can be run on [Piz Daint](https://www.cscs.ch/computers/piz-daint/). To enable everything, log in and clone this repository. Then, run the following commands:

```
cd scripts
bash create_env.sh
bash cmake.sh
```

This will create a virtual environment using python and installing a suitable CMake version. Afterwards, `cmake.sh` will load the environment and start the cmake-process. Running `make` can then be done without the virtual environment being active. If you have to active it yourself, execute the following two lines:
```
cd  ~
source hpc_env/bin/activate
```