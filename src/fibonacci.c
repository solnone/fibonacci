/*
 * Fast doubling Fibonacci algorithm
 *
 * https://www.nayuki.io/page/fast-fibonacci-algorithms
 * https://funloop.org/post/2017-04-14-computing-fibonacci-numbers.html
 * https://hackmd.io/@sysprog/linux2020-fibdrv
 */
#include "fibonacci.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static inline void _fibonacci_recursion_256(u256 *f, int n)
{
    if (n < 2) {
        ui256_set_si(f, n);
    } else {
        u256 a = {.low = 0, .high = 0};
        u256 b = {.low = 1, .high = 0};

        fibonacci_recursion_256(&a, n - 1);
        fibonacci_recursion_256(&b, n - 2);
        ui256_add(f, &a, &b);
    }
}

void fibonacci_recursion_256(u256 *f, int n)
{
    if (n > 370) {
        f->low = UINT128_MAX;
        f->high = UINT128_MAX;
        return;
    }
    _fibonacci_recursion_256(f, n);
}

/*
 * Fibonacci function is implemented either iteratively
 */
u64 fibonacci_iterative_64(int n)
{
    if (n > 93)
        return ~0;
    if (n < 2)
        return n;
    u64 a = 0, b = 1, f;
    for (size_t i = 2; i <= (size_t) n; i++) {
        f = a + b;
        a = b;
        b = f;
    }
    return f;
}

u128 fibonacci_iterative_128(int n)
{
    if (n > 186)
        return UINT128_MAX;

    if (n < 2)
        return n;

    u128 a = 0, b = 1, f;
    for (size_t i = 2; i <= (size_t) n; i++) {
        f = a + b;
        a = b;
        b = f;
    }
    return f;
}

void fibonacci_iterative_256(u256 *f, int n)
{
    if (n > 370) {
        f->low = UINT128_MAX;
        f->high = UINT128_MAX;
        return;
    }

    if (n < 2) {
        ui256_set_si(f, n);
        return;
    }

    u256 a = {.low = 0, .high = 0}, b = {.low = 1, .high = 0};

    for (size_t i = 2; i <= (size_t) n; i++) {
        ui256_add(f, &a, &b);
        ui256_set(&a, &b);
        ui256_set(&b, f);
    }
}

static inline void _fibonacci_iterative_128_mixing(int n, u128 *a, u128 *b)
{
    for (size_t i = 2; i <= (size_t) n; i++) {
        u128 f = *a + *b;
        *a = *b;
        *b = f;
    };
}

static inline void _fibonacci_iterative_256_mixing(int n, u256 *a, u256 *b)
{
    if (n > 370) {
        b->low = UINT128_MAX;
        b->high = UINT128_MAX;

    } else if (n <= 186) {
        _fibonacci_iterative_128_mixing(n, &(a->low), &(b->low));
    } else {
        _fibonacci_iterative_128_mixing(186, &(a->low), &(b->low));
        u256 f;
        for (size_t i = 187; i <= (size_t) n; i++) {
            ui256_add(&f, a, b);
            ui256_set(a, b);
            ui256_set(b, &f);
        }
    }
}

void fibonacci_iterative_mixing(u256 *f, int n)
{
    if (n == 0) {
        ui256_set_ui(f, 0);
        return;
    }
    u256 a = {.low = 0, .high = 0};
    ui256_set_ui(f, 1);
    _fibonacci_iterative_256_mixing(n, &a, f);
}

static inline void _fib_doubling_64(unsigned int n, u64 *a, u64 *b)
{
    // start from a=F(1) b=F(2), calculate loop count
    unsigned int count = fls(n) - 1;
    unsigned int mask = 1 << (count);

    *a = 1;  // F(1)=1
    *b = 1;  // F(2)=1
    for (size_t i = 0; i < count; i++) {
        mask >>= 1;

        // c = a * ((b << 1) - a)
        u64 c = *a * ((*b << 1) - *a);
        // d = a^2 + b^2
        u64 d = *a * *a + *b * *b;

        if (n & mask) {
            *a = d;
            *b = c + d;
        } else {
            *a = c;
            *b = d;
        }
    }
}

u64 fibonacci_doubling_64(int n)
{
    if (n > 93)
        return ~0;

    if (n < 2)
        return n;
    u64 a, b;
    _fib_doubling_64(n - 1, &a, &b);
    return b;
}

static inline void _fib_doubling_128(unsigned int n, u128 *a, u128 *b)
{
    // start from a=F(1) b=F(2), calculate loop count
    unsigned int count = fls(n) - 1;
    unsigned int mask = 1 << (count);

    *a = 1;  // F(1)=1
    *b = 1;  // F(2)=1
    for (size_t i = 0; i < count; i++) {
        mask >>= 1;

        // c = a * ((b << 1) - a)
        u128 c = *a * ((*b << 1) - *a);
        // d = a^2 + b^2
        u128 d = *a * *a + *b * *b;

        if (n & mask) {
            *a = d;
            *b = c + d;
        } else {
            *a = c;
            *b = d;
        }
    }
}

u128 fibonacci_doubling_128(int n)
{
    if (n > 186)
        return UINT128_MAX;

    if (n < 2)
        return n;
    u128 a, b;
    _fib_doubling_128(n - 1, &a, &b);
    return b;
}

static inline void _fib_doubling_256(unsigned int n, u256 *a, u256 *b)
{
    // start from a=F(1) b=F(2), calculate loop count
    unsigned int count = fls(n) - 1;
    unsigned int mask = 1 << (count);

    a->low = 1;  // F(1)=1
    a->high = 0;
    b->low = 1;  // F(2)=1
    b->high = 0;

    u256 c, d;
    for (size_t i = 0; i < count; i++) {
        mask >>= 1;
        // c = a * ((b << 1) - a)
        ui256_add(&c, b, b);
        ui256_sub(&c, &c, a);
        ui256_mul(&c, c.low, a->low);

        // d = a^2 + b^2
        ui256_mul(a, a->low, a->low);
        ui256_mul(b, b->low, b->low);
        ui256_add(&d, a, b);

        if (n & mask) {
            ui256_set(a, &d);
            ui256_add(b, &c, &d);
        } else {
            ui256_set(a, &c);
            ui256_set(b, &d);
        }
    }
}

void fibonacci_doubling_256(u256 *f, int n)
{
    if (n > 370) {
        f->low = UINT128_MAX;
        f->high = UINT128_MAX;
        return;
    }

    if (n < 2) {
        f->low = n;
        f->high = 0;
        return;
    }

    u256 a;
    _fib_doubling_256(n - 1, &a, f);
}

size_t fibonacci_doubling_mixing2(unsigned int n,
                                  unsigned int count,
                                  unsigned int max_count,
                                  struct mixing *f)
{
    size_t mask = 1 << (count);
    size_t i = 0;
    f->a.ui256.low = 1;
    f->a.ui256.high = 0;
    f->b.ui256.low = 1;
    f->b.ui256.high = 0;
    union union_mixing256 c, d;
    c.ui256.high = 0;
    d.ui256.high = 0;
    // n <= 93, 64 bits
    size_t bits = (count <= 5) ? count : 5;
    for (; i < bits; i++) {
        mask >>= 1;
        // c = a * ((b << 1) - a)
        c.ui64 = f->a.ui64 * ((f->b.ui64 << 1) - f->a.ui64);
        // d = a^2 + b^2
        d.ui64 = f->a.ui64 * f->a.ui64 + f->b.ui64 * f->b.ui64;

        if (n & mask) {
            f->a.ui64 = d.ui64;
            f->b.ui64 = c.ui64 + d.ui64;
        } else {
            f->a.ui64 = c.ui64;
            f->b.ui64 = d.ui64;
        }
    }

    // n <= 186, 128 bits
    bits = (count <= 6) ? count : 6;
    for (; i < bits; i++) {
        mask >>= 1;
        // c = a * ((b << 1) - a)
        c.ui128 = f->a.ui128 * ((f->b.ui128 << 1) - f->a.ui128);
        // d = a^2 + b^2
        d.ui128 = f->a.ui128 * f->a.ui128 + f->b.ui128 * f->b.ui128;

        if (n & mask) {
            f->a.ui128 = d.ui128;
            f->b.ui128 = c.ui128 + d.ui128;
        } else {
            f->a.ui128 = c.ui128;
            f->b.ui128 = d.ui128;
        }
    }

    for (; i < max_count; i++) {
        mask >>= 1;
        // c = a * ((b << 1) - a)
        ui256_add(&c.ui256, &f->b.ui256, &f->b.ui256);
        ui256_sub(&c.ui256, &c.ui256, &f->a.ui256);
        ui256_mul(&c.ui256, c.ui256.low, f->a.ui256.low);

        // d = a^2 + b^2
        ui256_mul(&f->a.ui256, f->a.ui256.low, f->a.ui256.low);
        ui256_mul(&f->b.ui256, f->b.ui256.low, f->b.ui256.low);
        ui256_add(&d.ui256, &f->a.ui256, &f->b.ui256);

        if (n & mask) {
            ui256_set(&f->a.ui256, &d.ui256);
            ui256_add(&f->b.ui256, &c.ui256, &d.ui256);
        } else {
            ui256_set(&f->a.ui256, &c.ui256);
            ui256_set(&f->b.ui256, &d.ui256);
        }
    }
    return i;
}

void fibonacci_doubling_mixing(u256 *f, int n)
{
    struct mixing mix;
    if (n > 370) {
        f->low = UINT128_MAX;
        f->high = UINT128_MAX;
    } else if (n < 2) {
        f->low = n;
        f->high = 0;
    } else {
        int k = n - 1;
        unsigned int count = fls(k) - 1;
        fibonacci_doubling_mixing2(k, count, count, &mix);
        ui256_set(f, &mix.b.ui256);
    }
}