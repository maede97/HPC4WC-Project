#pragma once
#include <HPC4WC/field.h>
namespace HPC4WC {

/**
 * @brief Apply the diffusion equation to a field.
 * 
 * Applies the equation \f$ \frac {\partial f}{\partial t}}=\alpha\nabla ^{2}f \f$.
 * @attention Applies the diffusion equation only to indices i and j (not k).
 */
class Diffusion {
public:
    /**
     * @brief Apply the equation.
     * @param [inout] f The field to apply the diffusion equation to.
     * @param [in] alpha The coefficient in front of the nabla operator.
     */
    static void apply(Field& f, const double& alpha = 1e-3);
};

/**
 * @todo Document and unittest.
 */
class SimpleDiffusion {
public:
    static void apply(Field& f, const double& alpha = 1e-3);
};

}  // namespace HPC4WC