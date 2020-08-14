/*
 * Fibonacci number
 *
 * fibonacci(0) = 0
 * fibonacci(1) = 1
 * fibonacci(n) = fibonacci(n-1) + fibonacci(n-2)  per n > 1
 *
 */
#include <stdbool.h>
#include "fibonacci_dijkstra_gmp.h"
#include "fibonacci_gmp.h"
#include "fibonacci_io.h"

static inline void report(char *name, mpz_ptr x)
{
    gmp_printf("%s = %Zd\n", name, x);
}

static inline bool equal(mpz_ptr x, mpz_ptr y)
{
    return (mpz_cmp(x, y) == 0);
}

int run(int start, int end)
{
    int r = 0;
    mpz_t x, y;
    mpz_init(x);
    mpz_init(y);
    for (int n = start; n <= end; n++) {
        printf("Fibonacci(%d):\n", n);
        fibonacci_doubling_gmp(x, n);
        report("doubling gmp", x);

        fibonacci_dijkstra_gmp(y, n);
        report("dijkstra gmp", y);
        r += !equal(x, y);


        fibonacci_iterative_gmp(y, n);
        report("iterative gmp", y);
        r += !equal(x, y);

        if (n <= 370) {
            u256 f256;
            fibonacci_doubling_256(&f256, n);
            mpz_set_ui256_ptr(y, &f256);
            report("doubling 256 bits", y);
            r += !equal(x, y);
        }

        if (n <= 186) {
            u128 f128 = fibonacci_doubling_128(n);
            mpz_set_ui128_ptr(y, &f128);
            report("doubling 128 bits", y);
            r += !equal(x, y);
        }

        if (n <= 93) {
            u64 f64 = fibonacci_iterative_64(n);
            mpz_set_ui(y, f64);
            report("iterative 64 bits", y);
            r += !equal(x, y);
        }

        printf("\n");
    }
    mpz_clear(x);
    mpz_clear(y);
    return r;
}

int main(int argc, char *argv[])
{
    int start, end;
    cmd_parse(&start, &end, -1, argc, argv);
    return run(start, end);
}