#pragma once
#include "clock_time.h"
#include "ui256.h"

#define UINT128_MAX (u128) ~0

#define RETURN_IF_NULL(obj, ret_val) \
    do {                             \
        if (!(obj))                  \
            return ret_val;          \
    } while (0)

static inline int get_max_number_by_bits(int bits)
{
    switch (bits) {
    case 64:
        return 93;
    case 128:
        return 186;
    case 256:
    default:
        return 370;
    }
}

void fibonacci_recursion_256(u256 *, int);

u64 fibonacci_iterative_64(int);
u128 fibonacci_iterative_128(int);
void fibonacci_iterative_256(u256 *, int);
void fibonacci_iterative_mixing(u256 *f, int);

u64 fibonacci_doubling_64(int);
u128 fibonacci_doubling_128(int);
void fibonacci_doubling_256(u256 *, int);
void fibonacci_doubling_mixing(u256 *, int);
size_t fibonacci_doubling_mixing2(unsigned int,
                                  unsigned int,
                                  unsigned int,
                                  struct mixing *);
