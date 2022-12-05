#include <iostream>

#include "result.hpp"

using Result = util::Result<int, const char *>;

int main()
{
    constexpr Result okay = 10;
    static_assert(okay.has_result());
    static_assert(okay.result() == 10);

    constexpr auto err = util::make_error<Result>("No value");
    static_assert(!err.has_result());
    static_assert(err.result_or(100) == 100);
    // static_assert(err.result() == 100); ** this failed

    return 0;
}
