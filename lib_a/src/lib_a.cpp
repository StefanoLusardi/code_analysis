#include <lib_a.hpp>

int lib_a::foo(int in_) const
{
    auto d = 2 * in_;
    float* f = new float[in_];
    f[d] = in_;
    return d;
}