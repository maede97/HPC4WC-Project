#pragma once

#include <HPC4WC/field.h>

namespace HPC4WC {

/**
 * @brief Create a cube in a field.
 */
class CubeInitialCondition {
public:
    /**
     * @brief Applies this initial condition on the field.
     * 
     * The field is split into 27 smaller cubes, where only the middle cube is set to constant 1.
     * @param[inout] field The field to apply the initial condition to.
     */
    static void apply(Field& field);
};

/**
 * @brief Applies a special IC where we fill diagonally 1.
 */
class DiagonalInitialCondition {
public:
    /**
     * @brief Applies this initial condition on the field.
     * @param[inout] field The field to apply the initial condition to.
     */
    static void apply(Field& field);
};

}  // namespace HPC4WC