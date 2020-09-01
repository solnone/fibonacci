# fibonacci
Fibonacci number

```
fibonacci(0) = 0,
fibonacci(1) = 1,
and fibonacci(n) = fibonacci(n-1) + fibonacci(n-2),  per n > 1
```

## Build & Run Fibonacci 64, 128, 256 bits without other libraries

```shell
$ cc -Wall -Wextra -g -O3 -march=native -o src/fib src/fib.c src/fibonacci.c src/fibonacci_io.c
$ echo 180 | src/fib
$ src/fib -s 91 -e 93 -b 64
$ src/fib -s 181 -e 186 -b 128
$ src/fib -s 367 -e 370 -b 256
```

## Required libraries

### Ubuntu | Debian

```shell
$ sudo apt-get install git build-essential
$ sudo apt-get install pkg-config gnuplot
$ sudo apt-get install libgmp-dev libglib2.0-dev
$ sudo apt-get install aspell clang-format cppcheck
$ sudo apt-get install autotools-dev autoconf automake libtool
```

### MacOS with Homebrew

```shell
$ xcode-select --install
$ /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"

$ brew install pkg-config gnuplot
$ brew install gmp glib
$ brew install aspell clang-format cppcheck
$ brew install autoconf automake libtool
```

## autoconf

```shell
$ autoreconf -ivf
```

## Build & Run Fibonacci with GMP library

```shell
$ cc -Wall -Wextra -g -O3 -march=native -o src/fib_doubling_mixing src/fib_doubling_mixing.c src/fibonacci.c src/fibonacci_gmp.c src/fibonacci_io.c -lgmp
$ echo 2000 | src/fib_doubling_mixing
```

## Configure and Make

```shell
$ CPPFLAGS="-Wall -Wextra -g -O3 -march=native" ./configure && make
```

## Run

```shell
$ echo 1000 | src/fib_doubling_gmp
$ echo 1000 | src/fib_iterative_gmp
$ src/main 183 187
```

## Tests

```shell
$ make check
```

## Scripts

```shell
$ # python
$ echo 99 | tests/fibonacci.py
$ # perl
$ echo 99 | tests/fibonacci.pl
$ # javascript
$ echo 99 | tests/fibonacci.js
$ # julia
$ echo 99 | tests/fibonacci.jl
```

## Java

```shell
$ javac tests/Fibonacci.java
$ echo 99 | java -cp tests Fibonacci
```

## Using AddressSanitizer

```shell
$ CC=clang CXX=clang++ CFLAGS="-Wall -Wextra -fsanitize=address -O1 -fno-omit-frame-pointer -g" CXXFLAGS=$CFLAGS ./configure
```

## Clang-Format

```shell
$ clang-format -style=file -i src/*.[ch] src/*.cpp
```

## Cppcheck

```shell
$ cppcheck --enable=all --inline-suppr --inconclusive --suppress=missingIncludeSystem --verbose src/*.[ch] src/*.cpp
```

## Valgrind

```shell
$ valgrind --tool=memcheck --leak-check=full --error-exitcode=1 -s src/main 99
```

## Install Git Hooks

```shell
$ scripts/install-git-hooks
```

## Plot

```shell
$ make plot
```

## References

[2020 年春季 Linux 核心設計課程作業 —— fibdrv - HackMD](https://hackmd.io/@sysprog/linux2020-fibdrv)

[Efficient implementations of Fibonacci function with interesting results - Domains / Numerics - JuliaLang](https://discourse.julialang.org/t/efficient-implementations-of-fibonacci-function-with-interesting-results/18123)

[Fast Fibonacci algorithms - Project Nayuki](https://www.nayuki.io/page/fast-fibonacci-algorithms)

[The Fastest Way to Compute the Nth Fibonacci Number: The Doubling Method - Linus's Blog](https://funloop.org/post/2017-04-14-computing-fibonacci-numbers.html)

[AddressSanitizer](https://github.com/google/sanitizers/wiki/AddressSanitizer)

[int128.h - chenshuo/recipes - GitHub](https://github.com/chenshuo/recipes/blob/master/basic/int128.h)

[c - how to print __uint128_t number using gcc? - Stack Overflow](https://stackoverflow.com/questions/11656241/how-to-print-uint128-t-number-using-gcc)

## Libraries

[The GNU Multiple Precision Arithmetic Library (gmp)](https://gmplib.org/)

[GLib](https://wiki.gnome.org/Projects/GLib)
