#include "fibonacci_io.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * References
 * https://stackoverflow.com/questions/11656241/how-to-print-uint128-t-number-using-gcc
 */
int fprint_ui128_u(FILE *__restrict __stream, u128 ui128)
{
    int rc;
    if (ui128 > UINT64_MAX) {
        u128 leading = ui128 / P10_UINT64;
        u64 trailing = ui128 % P10_UINT64;
        rc = fprint_ui128_u(__stream, leading);
        rc += fprintf(__stream, "%." TO_STRING(E10_UINT64) PRIu64, trailing);
    } else {
        u64 ui64 = ui128;
        rc = fprintf(__stream, "%" PRIu64, ui64);
    }
    return rc;
}

int _fprint_ui128_u(FILE *__restrict __stream, u128 ui128, bool *start)
{
    int rc;
    if (ui128 > UINT64_MAX) {
        u128 leading = ui128 / P10_UINT64;
        u64 trailing = ui128 % P10_UINT64;
        rc = _fprint_ui128_u(__stream, leading, start);
        *start = false;
        rc += fprintf(__stream, "%." TO_STRING(E10_UINT64) PRIu64, trailing);
    } else {
        u64 ui64 = ui128;
        if (*start) {
            rc = fprintf(__stream, "%" PRIu64, ui64);
            *start = false;
        } else {
            rc = fprintf(__stream, "%." TO_STRING(E10_UINT64) PRIu64, ui64);
        }
    }
    return rc;
}

int _fprint_ui256_u(FILE *__restrict __stream, u256 *ui256, bool *start)
{
    int rc;
    if (ui256->high != 0) {
        u256 quot;
        u128 rem;
        ui256_divrem(&quot, &rem, ui256, P10_UINT64);
        if (quot.high != 0) {
            rc = _fprint_ui256_u(__stream, &quot, start);
            rc += _fprint_ui128_u(__stream, rem, start);
        } else {
            rc = _fprint_ui128_u(__stream, quot.low, start);
            rc +=
                fprintf(__stream, "%." TO_STRING(E10_UINT64) PRIu64, (u64) rem);
        }
    } else {
        rc = _fprint_ui128_u(__stream, ui256->low, start);
    }
    return rc;
}

int fprint_ui256_u(FILE *__restrict __stream, u256 ui256)
{
    bool start = true;
    return _fprint_ui256_u(__stream, &ui256, &start);
}

void cmd_parse(int *start, int *end, int max, int argc, char *argv[])
{
    if (argc > 1) {
        *start = atoi(argv[1]);
    } else {
        printf("Fibonacci number F(n)\ninput n: ");
        if (scanf("%d", start) != 1) {
            *start = 0;
        }
        printf("\n");
    }
    if (*start < 0) {
        fprintf(stderr, "The input value must be a positive integer\n");
        *start = 0;
    }

    if (argc > 2) {
        *end = atoi(argv[2]);
    } else {
        *end = *start;
    }

    if (*start > *end) {
        *start = *end;
    }

    if (max > 0) {
        if (*start > max) {
            *start = max;
        }
        if (*end > max) {
            *end = max;
        }
    }
}
