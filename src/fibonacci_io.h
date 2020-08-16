#pragma once

#include <stdbool.h>
#include <stdio.h>
#include "fibonacci.h"

/*      UINT64_MAX 18446744073709551615ULL */
#define P10_UINT64 10000000000000000000ULL /* 19 zeroes */
#define E10_UINT64 19

#define STRINGIZER(x) #x
#define TO_STRING(x) STRINGIZER(x)

struct fib_params {
    int n1;
    int n2;
    int bits;
    int mode;
    bool out_time;
};

int fprint_ui128_u(FILE *__restrict __stream, u128 ui128);
int fprint_ui256_u(FILE *__restrict __stream, u256 ui256);
void cmd_parse(int *start, int *end, int max, int argc, char *argv[]);
void cmd_getopt(struct fib_params *, int argc, char *argv[]);
