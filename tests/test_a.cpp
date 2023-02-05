#include <gtest/gtest.h>
#include <lib_a/lib_a.hpp>

TEST(suite_1, test_a)
{
    auto in = 4;
    auto expected = 8;
    lib_a liba;
    ASSERT_EQ(expected, liba.foo(in));
}