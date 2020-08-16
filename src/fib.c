#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "fibonacci.h"
#include "fibonacci_io.h"

typedef void (*fib_f)(int, int);
typedef u64 (*fib64_f)(int);
typedef u128 (*fib128_f)(int);
typedef void (*fib256_f)(u256 *, int);

static void fib_64(fib64_f func, int n, int out_time)
{
    CLOCK_TIME t1, t2;
    CLOCK_GETTIME(t1);
    unsigned long long f = func(n);
    CLOCK_GETTIME(t2);
    if (out_time)
        fprintf(stderr, "%d %lld\n", n, GETTIME(t2) - GETTIME(t1));
    printf("%d %llu\n", n, f);
}

static void fib_128(fib128_f func, int n, int out_time)
{
    CLOCK_TIME t1, t2;
    CLOCK_GETTIME(t1);
    u128 f128 = func(n);
    CLOCK_GETTIME(t2);
    if (out_time)
        fprintf(stderr, "%d %lld\n", n, GETTIME(t2) - GETTIME(t1));
    fprintf(stdout, "%d ", n);
    fprint_ui128_u(stdout, f128);
    fprintf(stdout, "\n");
}

static void fib_256(fib256_f func, int n, int out_time)
{
    CLOCK_TIME t1, t2;
    CLOCK_GETTIME(t1);
    u256 f256;
    func(&f256, n);
    CLOCK_GETTIME(t2);

    if (out_time)
        fprintf(stderr, "%d %lld\n", n, GETTIME(t2) - GETTIME(t1));
    fprintf(stdout, "%d ", n);
    fprint_ui256_u(stdout, f256);
    fprintf(stdout, "\n");
}

// cppcheck-suppress unusedFunction
static void fib_doubling_64(int n, int out_time)
{
    fib_64(&fibonacci_doubling_64, n, out_time);
}

// cppcheck-suppress unusedFunction
static void fib_doubling_128(int n, int out_time)
{
    fib_128(&fibonacci_doubling_128, n, out_time);
}

// cppcheck-suppress unusedFunction
static void fib_doubling_256(int n, int out_time)
{
    fib_256(&fibonacci_doubling_256, n, out_time);
}

// cppcheck-suppress unusedFunction
static void fib_doubling_mixing(int n, int out_time)
{
    fib_256(&fibonacci_doubling_mixing, n, out_time);
}

// cppcheck-suppress unusedFunction
static void fib_iterative_64(int n, int out_time)
{
    fib_64(&fibonacci_iterative_64, n, out_time);
}

// cppcheck-suppress unusedFunction
static void fib_iterative_128(int n, int out_time)
{
    fib_128(&fibonacci_iterative_128, n, out_time);
}

// cppcheck-suppress unusedFunction
static void fib_iterative_256(int n, int out_time)
{
    fib_256(&fibonacci_iterative_256, n, out_time);
}

// cppcheck-suppress unusedFunction
static void fib_iterative_mixing(int n, int out_time)
{
    fib_256(&fibonacci_iterative_mixing, n, out_time);
}

// cppcheck-suppress unusedFunction
static void fib_recursion_256(int n, int out_time)
{
    fib_256(&fibonacci_recursion_256, n, out_time);
}

static inline fib_f get_function(int mode, int bits, int n1, int n2)
{
    switch (mode) {
    case 1:
        if (bits == 0) {
            printf("Mixing bits doubling F(%d)-F(%d):\n", n1, n2);
        } else {
            printf("%d bits doubling F(%d)-F(%d):\n", bits, n1, n2);
        }
        switch (bits) {
        case 64:
            return &fib_iterative_64;
        case 128:
            return &fib_iterative_128;
        case 256:
            return &fib_iterative_256;
        default:
            return &fib_iterative_mixing;
        }
        break;

    case 0:
    default:
        if (bits == 0) {
            printf("Mixing bits doubling F(%d)-F(%d):\n", n1, n2);
        } else {
            printf("%d bits doubling F(%d)-F(%d):\n", bits, n1, n2);
        }
        switch (bits) {
        case 64:
            return &fib_doubling_64;
        case 128:
            return &fib_doubling_128;
        case 256:
            return &fib_doubling_256;
        default:
            return &fib_doubling_mixing;
        }
        break;
    }
}

int main(int argc, char *argv[])
{
    struct fib_params p;
    cmd_getopt(&p, argc, argv);
    fib_f func = get_function(p.mode, p.bits, p.n1, p.n2);
    for (int n = p.n1; n <= p.n2; n++) {
        func(n, p.out_time);
    }
}
