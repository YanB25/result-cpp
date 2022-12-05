#include <iostream>

#include "result.hpp"

using Result = util::Result<int, const char *>;

Result get_okay()
{
    return 10;  // also, return util::make_result(10)
}
Result get_error()
{
    return util::make_error<Result>("It is an error.");
}

void basic(const Result &result)
{
    if (result)
    {
        // or result.result()
        std::cout << "result: " << *result << std::endl;
    }
    else
    {
        std::cout << "error: " << result.error() << std::endl;
        std::cout << "result_or(10): " << result.result_or(10) << std::endl;

        // will through util::bad_result_access:
        // int val = *result;
    }
}

int main()
{
    auto r1 = get_okay();
    basic(r1);
    auto r2 = get_error();
    basic(r2);
    return 0;
}
