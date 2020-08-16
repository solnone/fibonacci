#include "fibonacci_io.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

static void usage(char *cmd)
{
    printf("Usage: %s [-h] [-s start][-e end][-b bits][-t][-m mode]\n", cmd);
    printf("\t-h         Print this information\n");
    printf("\t-s start   Start number, default: 0\n");
    printf("\t-e end     End number, default: 370\n");
    printf("\t-b bits    Use bits: 0, 64, 128, 256, default: 0 -> mixing\n");
    printf("\t-t         Calculate the execution time of a method\n");
    printf("\t-m method  Method: doubling, iterative, default: doubling\n");
    exit(0);
}

#define BUFSIZE 256
void cmd_getopt(struct fib_params *p, int argc, char *argv[])
{
    p->n1 = 0;
    p->bits = 0;
    p->mode = 0;
    p->out_time = false;
    if (1 < argc) {
        p->n2 = 370;
        char buf[BUFSIZE];
        buf[BUFSIZE - 1] = '\0';
        int ch;
        while ((ch = getopt(argc, argv, "hs:e:b:tm:")) != -1) {
            switch (ch) {
            case 'h':
                usage(argv[0]);
                break;
            case 's':
                p->n1 = atoi(strncpy(buf, optarg, BUFSIZE - 1));
                break;
            case 'e':
                p->n2 = atoi(strncpy(buf, optarg, BUFSIZE - 1));
                break;
            case 'b':
                p->bits = atoi(strncpy(buf, optarg, BUFSIZE - 1));
                break;
            case 't':
                p->out_time = true;
                break;
            case 'm':
                strncpy(buf, optarg, BUFSIZE - 1);
                if (strcmp("iterative", buf) == 0) {
                    p->mode = 1;
                }
                break;
            default:
                break;
            }
        }
    } else {
        p->n2 = 0;
        printf("Fibonacci number F(n)\ninput n: ");
        if (scanf("%d", &p->n1) != 1) {
            p->n1 = 0;
        }
        printf("\n");
    }


    int max = get_max_number_by_bits(p->bits);
    if (p->n1 < 0) {
        p->n1 = 0;
    }
    if (max < p->n1) {
        p->n1 = max;
    }
    if (p->n2 < p->n1) {
        p->n2 = p->n1;
    }
    if (max < p->n2) {
        p->n2 = max;
    }
    if (p->out_time) {
        printf("log the spend time in stderr: number time(ns)\n");
    }
}
