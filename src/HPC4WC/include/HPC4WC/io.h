#pragma once
#include <HPC4WC/field.h>

#include <iostream>

namespace HPC4WC {

class IO {
public:
    static void write(std::ostream& stream, const Field& f, Field::const_idx_t& k);
};
}  // namespace HPC4WC