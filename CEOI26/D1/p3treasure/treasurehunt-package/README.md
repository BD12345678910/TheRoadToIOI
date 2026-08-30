# Local package for CEOI 2026 Day 1, Problem 3: Treasure Hunt

Files:

- `treasurehuntlib.h`
- `treasurehuntlib-public.cpp`
- `example.cpp`
- `hunts.txt`

Compile:

```sh
g++ -std=c++17 -O2 example.cpp treasurehuntlib-public.cpp -o example
./example
```

The library writes diagnostics to `stderr`.

## Loading your own hunts

At the beginning of your local program, before the first `NextHunt`, call:

```cpp
InitFromFile("hunts.txt");
```

The counted format is:

```text
H
N K
x1 y1
...
xK yK
```

repeated `H` times.

The library also accepts the same sequence without the initial `H`, continuing until EOF.

## Submission warning

`InitFromFile` is a local-testing extension. Remove its call before submitting.
Your submitted program must not use standard input or standard output.

This is a compatible simulator reconstructed from the task statement, not the
organisers' exact unpublished implementation.
