#pragma once
#include <HPC4WC/field.h>

namespace HPC4WC {
/**
 * Periodic boundary conditions, meaning values will be copied over.
 * @attention Works only on i and j indices.
 * @todo Customize where to apply the boundary conditions.
 */
class PeriodicBoundaryConditions {
public:
    /**
     * @brief Apply periodic boundary conditions on a field.
     * @param[inout] field The field to apply the boundary conditions to.
     */
    static void apply(Field& field);
};

}  // namespace HPC4WC