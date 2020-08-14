/*
 * Fibonacci number
 *
 * fibonacci(0) = 0
 * fibonacci(1) = 1
 * fibonacci(n) = fibonacci(n-1) + fibonacci(n-2)  per n > 1
 *
 */
#include "fibonacci.h"
#include "fibonacci_gmp.h"
#include "fibonacci_io.h"

int main(int argc, char *argv[])
{
    mpz_t x;
    mpz_init(x);
    int start, end;
    cmd_parse(&start, &end, -1, argc, argv);
    for (int n = start; n <= end; n++) {
        fibonacci_iterative_gmp(x, n);
        gmp_printf("%Zd\n", x);
    }
    mpz_clear(x);
}
