assert++
========

- assert++ is an assert replacement written in C++03.
- assert++ is smart. LHS/RHS values are printed as long as they are `ostream` friendly.
- assert++ is cross-platform. crash handler fallbacks to `assert()` symbol.
- assert++ is header only.
- assert++ is BOOST licensed.

### sample

```c++
#include "assert++.hpp"

int main() {
    int a = 1, b = 2;

    assert( a < b );
    assert( a > b );
}
```

### possible output

```
#~/> g++ sample.cc && ./a.out
<assert++> says: expression failed! (a > b) -> (1 > 2) -> (unexpected) at sample.cc:7
```
