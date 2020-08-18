#include <stdlib.h>
#include "fibonacci_gmp.h"
#include "fibonacci_io.h"

void fibonacci_doubling_gmp_time_proxy(mpz_t value, int n)
{
    long long times[REPEAT_TIME];
    for (size_t i = 0; i < REPEAT_TIME; i++) {
        CLOCK_TIME t1, t2;
        CLOCK_GETTIME(t1);
        fibonacci_doubling_gmp(value, n);
        CLOCK_GETTIME(t2);
        times[i] = GETTIME(t2) - GETTIME(t1);
    }
    qsort(times, REPEAT_TIME, sizeof(long long), cmp);
    fprintf(stderr, "%d %lld\n", n, times[REPEAT_TIME >> 1]);
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
        func = fibonacci_doubling_gmp_time_proxy;
        printf("log the spend time in stderr: number time(ns)\n");
    } else {
        func = fibonacci_doubling_gmp;
    }
    for (int n = start; n <= end; n++) {
        func(x, n);
        gmp_printf("%Zd\n", x);
    }
    mpz_clear(x);
}
