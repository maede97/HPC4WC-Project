#include <HPC4WC/field.h>
#include <gtest/gtest.h>

TEST(Field, Constructor) {
    using namespace HPC4WC;
    Field f_small(1, 1, 1, 1);         // constant zero
    Field f_constant(2, 2, 2, 2, 3.);  // constant 3
    Field f2(2, 2, 2, 2);
    Field f_large(1000, 1000, 100, 2);  // large field
}

TEST(Field, AccessGood) {
    using namespace HPC4WC;
    Field f(2, 2, 2, 2, 3.);
    EXPECT_DOUBLE_EQ(f(0, 0, 0), 3);  // halo is also 3.
    EXPECT_DOUBLE_EQ(f(2, 2, 0), 3.);  // constant value

    f(1, 1, 0) = 4.;
    EXPECT_DOUBLE_EQ(f(1, 1, 1), 3.);
    EXPECT_FLOAT_EQ(f(1, 1, 0), 4.);

    EXPECT_NO_THROW(f(5, 0, 0));
    EXPECT_NO_THROW(f(0, 5, 0));
    EXPECT_NO_THROW(f(0, 0, 1));
}

TEST(Field, AccessBad) {
    using namespace HPC4WC;
    Field f(2, 2, 2, 2, 3.);
    EXPECT_THROW(f(-1, 0, 0), std::out_of_range);
    EXPECT_THROW(f(6, 0, 0), std::out_of_range);
    EXPECT_THROW(f(0, -1, 0), std::out_of_range);
    EXPECT_THROW(f(0, 6, 0), std::out_of_range);
    EXPECT_THROW(f(0, 0, -1), std::out_of_range);
    EXPECT_THROW(f(0, 0, 2), std::out_of_range);
}

TEST(Field, SetFrom) {
    using namespace HPC4WC;
    Field f1(10, 10, 2, 2, 1.);
    Field f2(10, 10, 2, 2, 3.);
    Field f3(10, 10, 2, 1);  // different num_halo
    Field f4(9, 10, 2, 2);   // different i
    Field f5(10, 9, 2, 2);   // different j
    Field f6(10, 10, 3, 2);  // different k

    EXPECT_DOUBLE_EQ(f1(2, 2, 1), 1.);
    EXPECT_DOUBLE_EQ(f2(2, 2, 1), 3.);
    EXPECT_NO_THROW(f1.setFrom(f2));
    EXPECT_DOUBLE_EQ(f1(2, 2, 1), 3.);

    EXPECT_THROW(f1.setFrom(f3), std::logic_error);
    EXPECT_THROW(f1.setFrom(f4), std::logic_error);
    EXPECT_THROW(f1.setFrom(f5), std::logic_error);
    EXPECT_THROW(f1.setFrom(f6), std::logic_error);
}