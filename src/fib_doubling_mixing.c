#include <stdlib.h>
#include "fibonacci.h"
#include "fibonacci_gmp.h"
#include "fibonacci_io.h"

static void _doubling_mixing(unsigned int n, unsigned int count, mpz_t b)
{
    struct mixing mix;
    size_t i = 7;
    if (count <= i) {
        fibonacci_doubling_mixing2(n, count, count, &mix);
        mpz_set_ui256_ptr(b, &mix.b.ui256);
    } else {
        fibonacci_doubling_mixing2(n, count, i, &mix);
        mpz_t a, c, d;
        mpz_init(a);
        mpz_init(c);
        mpz_init(d);
        mpz_set_ui256_ptr(a, &mix.a.ui256);
        mpz_set_ui256_ptr(b, &mix.b.ui256);
        size_t mask = 1 << (count - i);
        for (; i < count; i++) {
            mask >>= 1;
            // c = a * ((b << 1) - a)
            mpz_mul_si(c, b, 2);
            mpz_sub(c, c, a);
            mpz_mul(c, c, a);

            // d = a^2 + b^2
            mpz_pow_ui(a, a, 2);  // mpz_mul(a, a, a);
            mpz_pow_ui(b, b, 2);  // mpz_mul(b, b, b);
            mpz_add(d, a, b);

            if (n & mask) {
                mpz_set(a, d);
                mpz_add(b, c, d);
            } else {
                mpz_set(a, c);
                mpz_set(b, d);
            }
        }
        mpz_clear(a);
        mpz_clear(c);
        mpz_clear(d);
    }
}

void doubling_mixing(mpz_t value, int n)
{
    if (n < 2) {
        return mpz_set_si(value, n);
    } else {
        int k = n - 1;
        unsigned int count = fls(k) - 1;
        _doubling_mixing(k, count, value);
    }
}

void doubling_mixing_time_proxy(mpz_t value, int n)
{
    CLOCK_TIME t1, t2;
    CLOCK_GETTIME(t1);
    doubling_mixing(value, n);
    CLOCK_GETTIME(t2);
    fprintf(stderr, "%d %lld\n", n, GETTIME(t2) - GETTIME(t1));
}

int main(int argc, char *argv[])
{
    mpz_t x;
    mpz_init(x);

    int start, end;
    cmd_parse(&start, &end, -1, argc, argv);

    int out_time = (argc > 4) ? atoi(argv[4]) : 0;
    fib_gmp_f func;
    if (out_time) {
        func = &doubling_mixing_time_proxy;
        printf("log the spend time in stderr: number time(ns)\n");
    } else {
        func = &doubling_mixing;
    }
    for (int n = start; n <= end; n++) {
        func(x, n);
        gmp_printf("%Zd\n", x);
    }
    mpz_clear(x);
}
