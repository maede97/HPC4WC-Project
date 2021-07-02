#pragma once
#include <HPC4WC/field.h>

#include <iostream>

namespace HPC4WC {

class IO {
public:
    /**
     * @brief Write a field to a stream.
     * @param[inout] stream The stream to which the file should be written (can be std::cout, or i.e. std::ofstream)
     * @param[in] f The field to write.
     * @param[in] k The last index of the field, which means this writes only a i-j-plane.
     */
    static void write(std::ostream& stream, const Field& f, Field::const_idx_t& k);
};
}  // namespace HPC4WC