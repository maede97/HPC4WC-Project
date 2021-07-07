#pragma once
#include <string>

namespace HPC4WC {

// use https://stackoverflow.com/questions/35050381/execute-binary-from-c-without-shell/35050382
class AutoTuner {
public:
    AutoTuner(const char* exe_name);

    void search() const;

public:
    // This should be made private.
    std::string open_with_arguments(const std::string& arguments) const;

private:
    const char* m_exe_name;
    unsigned m_max_wait_millseconds = 15000; // 15s
};
}  // namespace HPC4WC