#include <gmpxx.h>
#include <iostream>

void fib(mpz_ptr value, int n)
{
    if (n < 2) {
        return mpz_set_si(value, n);
    }
    mpz_t a;
    mpz_init(a);
    fib(a, n - 1);
    fib(value, n - 2);
    mpz_add(value, a, value);
    mpz_clear(a);
}

int main()
{
    int n;
    std::cin >> n;
    if (n < 0) {
        std::cerr << "The input value must be a positive integer" << std::endl;
    } else {
        mpz_class f;
        fib(f.get_mpz_t(), n);
        std::cout << f << std::endl;
    }
}
