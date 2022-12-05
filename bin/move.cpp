#include <iostream>

#include "result.hpp"

struct Pin
{
    Pin() = default;
    Pin(Pin &&) = default;
    Pin &operator=(Pin &&) = default;

    Pin(const Pin &) = delete;
    Pin &operator=(const Pin &) = delete;
};

inline std::ostream &operator<<(std::ostream &os, const Pin &)
{
    os << "Pin";
    return os;
}

using Result = util::Result<Pin, const char *>;

Result get_okay()
{
    return Pin{};  // also, return util::make_result()
}
Result get_error()
{
    return util::make_error<Result>("It is an error.");
}

void basic_rvalue(Result &&result)
{
    if (result)
    {
        // or pin2 = std::move(result).result()
        auto pin2 = *std::move(result);
        std::cout << "moved another pin: " << pin2 << std::endl;
    }
    else
    {
        std::cout << "error: " << result.error() << std::endl;

        result.emplace();
        std::cout << "after emplace: " << *result << std::endl;
    }
}

int main()
{
    auto r1 = get_okay();
    basic_rvalue(std::move(r1));
    auto r2 = get_error();
    basic_rvalue(std::move(r2));
    return 0;
}
