# arpsarge

Single-header argument parser. C++17

### Example

Consider the following executable call:

```sh
./app --client --private true --port 45678 --addr 123.88.134.64 -b 0.125 -m 8
```

```cpp
#include "arpsarge.hpp"

std::int32_t main(std::int32_t const argc, char const *const *const argv) {
    /// Initialize the parser
    arpsarge argp{argc, argv};

    /// Get option with no parameters
    auto const is_server = argp.has("--server");

    /// Get option with values
    auto const is_private = argp.getv<bool>("--private");
    auto const max_players = argp.getv<std::uint32_t>("-m");
    auto const min_buy_in = argp.getv<float>("-b");
    auto const address = argp.getv<std::string_view>("--addr");

    ...

    return 0;
}
```

### Design principles

- Easy to include
  - Single header, couldn't get much easier than this :)
- Ergonomic to use
  - Simple, short interface for getting specific arguments
