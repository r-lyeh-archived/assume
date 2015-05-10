Assume <a href="https://travis-ci.org/r-lyeh/assume"><img src="https://api.travis-ci.org/r-lyeh/assume.svg?branch=master" align="right" /></a>
=======

- Assume is a smarter assert replacement (C++03).
- Assume is handy. LHS/RHS values are printed as long as they are `ostream` friendly.
- Assume is cross-platform. Crash handler fallbacks to `assert()` symbol.
- Assume is header only.
- Assume is zlib/libpng licensed.

## sample

```c++
#include "assume.hpp"

int main() {
    int a = 1, b = 2;

    assume( a < b );
    assume( a > b );
}
```

## possible output

```c++
#~/> g++ sample.cc && ./a.out
<assume.hpp> says: expression failed! (a > b) -> (1 > 2) -> (unexpected) at sample.cc:7
```
