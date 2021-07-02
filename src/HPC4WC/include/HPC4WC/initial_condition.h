#pragma once

#include <HPC4WC/field.h>

namespace HPC4WC {

class CubeInitialCondition {
public:
    static void apply(Field& field);
};

class DiagonalInitialCondition {
public:
    static void apply(Field& f);
};

}  // namespace HPC4WC