#pragma once
#include <HPC4WC/field.h>

#include <string>

namespace HPC4WC {
/**
 * 
 * Examples (with executables/autotune_search.cpp):
 * 
 * EXECUTE NORMAL PROGRAMS
 * Windows:
 * `.\autotune_search.exe --executable diffusion2d --exe-args="nk=10"`
 * Linux:
 * `./autotune_search --executable diffusion2d --exe-args="nk=10"`
 * 
 * EXECUTE MPI PROGRAMS where the search goes over the parameter "n" (passed to mpiexec)
 * The final call be will be something like "`mpiexec -n X diffusion2d --openmp-num-threads=2`", which means, that the OpenMP num threads argument will be used inside diffusion2d.
 * Windows:
 * `.\autotune_search.exe --executable mpiexec --exe-args="diffusion2d --openmp-num-threads=2"`
 * Linux:
 * `./autotune_search --executable mpiexec --exe-args="diffusion2d --openmp-num-threads=2"`
 */
class AutoTuner {
public:
    /**
     * @brief Create an autotuner, based on the executable and additional arguments passed to it.
     * @param[in] exe_name
     * @param[in] exe_args
     */
    AutoTuner(const char* exe_name, const char* exe_args);
    
    /**
     * @brief Add a variable to search.
     * @param[in] argument
     * @param[in] lower_bound
     * @param[in] upper_bound
     * @param[in] step_size
     * @attention The upper bound is inclusive!
     */
    void add_range_argument(const char* argument, Field::const_idx_t& lower_bound, Field::const_idx_t& upper_bound, Field::const_idx_t& step_size = 1);
    void add_bool_argument(const char* argument);

    /**
     * @brief Search over all parameters.
     * @todo The search is not fully implemented! Considers only the first argument to search through at the moment.
     */
    void search() const;

private:
    // returns seconds
    double open_with_arguments(const std::string& arguments) const;
    const char* m_exe_name;
    const char* m_exe_args;
    unsigned m_max_wait_millseconds = 15000;  // 15s

    std::vector<std::pair<const char*, std::vector<Field::idx_t>>> m_arguments;
};
}  // namespace HPC4WC