#pragma once
#include <HPC4WC/field.h>
namespace HPC4WC {
class Diffusion {
public:
    static void apply(Field& f, Field& tmp, const double& alpha = 1e-3);
};
}  // namespace HPC4WC