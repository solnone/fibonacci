#include <gmpxx.h>
#include <iostream>
#include "fibonacci_gmp.h"

int main()
{
    int n;
    std::cin >> n;
    mpz_class f;
    fibonacci_doubling_gmp(f.get_mpz_t(), n);
    std::cout << f << std::endl;
}
