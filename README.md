# Result-cpp

Result-cpp is a header-only library that provides a [rust-like](https://doc.rust-lang.org/std/result/) Result abstraction (i.e., `Result<T, E>`) following C++17 standard.

The header-only file is [here](include/result.hpp).

## Basic Usage

Define you customized result.

``` c++
using Result = util::Result<int, const char *>;
```

To construct a result.

``` c++
Result get_okay()
{
    return 10;  // also, return util::make_result(10)
}
Result get_error()
{
    return util::make_error<Result>("It is an error.");
}
```

The interface of `result` is pretty much similar to [std::optional](https://en.cppreference.com/w/cpp/utility/optional).

- At any given point in time, `result<V, E>` either contains a value or an error
- The value (or error) contained by `result<V, E>` is guaranteed to be allocated as part of the `result` object footprint. Thus, a `result` models an object, not a pointer, even though `operator*()` and `operator->()` are defined.


``` c++
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

        // will throw util::bad_result_access:
        // int val = *result;
    }
}
```

## Advanced

### Move semantics

`result` considers move semantics, see the [example](bin/move.cpp).

Assume `Pin` is an object that is not *copyable* (but *movable*).

``` c++
void basic_rvalue(Result &&result) // note the R-reference here
{
    if (result)
    {
        // or pin2 = std::move(result).result()
        auto pin2 = *std::move(result);
        std::cout << "moved another pin: " << pin2 << std::endl;
    }
    else
    {
        result.emplace(); // emplace performs *in-place* construction
        std::cout << "after emplace: " << *result << std::endl;
    }
}
```

### constexpr

`result` supports `constexpr`, see the [example](bin/constexpr.cpp).

``` c++
constexpr Result okay = 10;
static_assert(okay.has_result());
static_assert(okay.result() == 10);

constexpr auto err = util::make_error<Result>("No value");
static_assert(!err.has_result());
static_assert(err.result_or(100) == 100);
// static_assert(err.result() == 100); ** this failed
```