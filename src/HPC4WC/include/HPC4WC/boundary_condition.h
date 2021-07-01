#pragma once
#include <HPC4WC/field.h>

namespace HPC4WC {
class PeriodicBoundaryConditions {
public:
    // potentially: set periodicity on axis
    static void apply(Field& field);
};

}  // namespace HPC4WC