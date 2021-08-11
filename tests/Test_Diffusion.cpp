#include <HPC4WC/config.h>
#include <HPC4WC/diffusion.h>
#include <HPC4WC/initial_condition.h>
#include <gtest/gtest.h>

TEST(Diffusion, Diffusion) {
    // TODO
}

TEST(Diffusion, SimpleDiffusion) {
    // TODO
}

TEST(Diffusion, Comparison) {
    using namespace HPC4WC;
    Field f1(10, 10, 10, 2);
    Field f2(10, 10, 10, 2);

    Config::BLOCK_SIZE_I = 5;
    Config::BLOCK_SIZE_J = 5;

    CubeInitialCondition::apply(f1);
    CubeInitialCondition::apply(f2);

    EXPECT_EQ(f1, f2);

    for (int i = 0; i < 100; i++) {
        Diffusion::apply(f1);
        SimpleDiffusion::apply(f2);

        EXPECT_EQ(f1, f2);
    }
}