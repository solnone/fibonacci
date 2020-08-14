/*
 * Fast doubling Fibonacci algorithm
 *
 * https://www.nayuki.io/page/fast-fibonacci-algorithms
 * https://funloop.org/post/2017-04-14-computing-fibonacci-numbers.html
 * https://hackmd.io/@sysprog/linux2020-fibdrv
 */
#include "fibonacci_gmp.h"

void mpz_set_ui128_ptr(mpz_ptr x, u128 *y)
{
    mpz_set_ui(x, *y >> 64);
    mpz_mul_2exp(x, x, 64);
    mpz_add_ui(x, x, *y);
}

void mpz_set_ui256_ptr(mpz_ptr x, u256 *y)
{
    mpz_set_ui(x, y->high >> 64);
    mpz_mul_2exp(x, x, 64);
    mpz_add_ui(x, x, y->high);
    mpz_mul_2exp(x, x, 64);
    mpz_add_ui(x, x, y->low >> 64);
    mpz_mul_2exp(x, x, 64);
    mpz_add_ui(x, x, y->low);
}

/**
 * Fibonacci number using the doubling method
 *
 * @param n the number n, n > 0
 * @param a return F(n)
 * @param b return F(n+1)
 */
static void _fib(unsigned int n, mpz_t a, mpz_t b)
{
    // start from a=F(1) b=F(2), calculate loop count
    size_t count = fls(n) - 1;
    unsigned int mask = 1 << (count);

    mpz_set_si(a, 1);  // F(1)=1
    mpz_set_si(b, 1);  // F(2)=1
    mpz_t c, d;
    mpz_init(c);
    mpz_init(d);
    for (size_t i = 0; i < count; i++) {
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
    mpz_clear(c);
    mpz_clear(d);
}

/**
 * Fibonacci number using the doubling method
 *
 * @param value return F(n)
 * @param n     the number n
 */
void fibonacci_doubling_gmp(mpz_t value, int n)
{
    if (n < 2) {
        return mpz_set_si(value, n);
    } else {
        mpz_t a;
        mpz_init(a);
        _fib(n - 1, a, value);
        mpz_clear(a);
    }
}

/**
 * Fibonacci number using iteration
 *
 * @param value return F(n)
 * @param n     the number n
 */
void fibonacci_iterative_gmp(mpz_t f, int n)
{
    if (n < 2)
        return mpz_set_si(f, n);

    mpz_t f0, f1;
    mpz_init_set_si(f0, 0);
    mpz_init_set_si(f1, 1);
    for (size_t i = 2; i <= (size_t) n; i++) {
        mpz_add(f, f0, f1);
        mpz_set(f0, f1);
        mpz_set(f1, f);
    }
    mpz_clear(f0);
    mpz_clear(f1);
}
