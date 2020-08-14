#pragma once

#include <gmp.h>
#include <stdint.h>
#include "clock_time.h"
#include "ui256.h"

#ifdef __cplusplus
extern "C" {
#endif

void mpz_set_ui128_ptr(mpz_ptr, u128 *);
void mpz_set_ui256_ptr(mpz_ptr, u256 *);
void fibonacci_doubling_gmp(mpz_t, int);
void fibonacci_iterative_gmp(mpz_t, int);

typedef void (*fib_gmp_f)(mpz_t, int);

#ifdef __cplusplus
}
#endif
