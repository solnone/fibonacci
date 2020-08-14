/*
 * Dijkstra’s recurrence equation
 *
 * F(2n)  = F(n) ( 2F(n-1) + F(n) )
 * F(2n+1) = F(n)^2 + F(n+1)^2
 *
 * References
 * https://discourse.julialang.org/t/efficient-implementations-of-fibonacci-function-with-interesting-results/18123
 */
#include <glib.h>
#include <gmp.h>

static mpz_ptr _fib(GHashTable *hash, int n)
{
    mpz_ptr p = g_hash_table_lookup(hash, GINT_TO_POINTER(n));
    if (!p) {
        p = g_malloc(sizeof(mpz_t));
        mpz_ptr p1, p2;
        int m = n >> 1;
        if (n % 2 == 0) {
            p1 = _fib(hash, m);
            p2 = _fib(hash, m - 1);
            mpz_init_set(p, p2);
            mpz_mul_si(p, p, 2);
            mpz_add(p, p, p1);
            mpz_mul(p, p, p1);
        } else {
            p1 = _fib(hash, m + 1);
            p2 = _fib(hash, m);
            mpz_init_set(p, p2);
            mpz_mul(p, p, p);
            mpz_t x;
            mpz_init_set(x, p1);
            mpz_mul(x, x, x);
            mpz_add(p, p, x);
            mpz_clear(x);
        }
        g_hash_table_insert(hash, GINT_TO_POINTER(n), p);
    }
    return p;
}

/*
 * brief Free a key-value pair inside the hash table.
 */
static void _free(__attribute__((unused)) gpointer key,
                  gpointer value,
                  __attribute__((unused)) gpointer user_data)
{
    mpz_clear(value);
    g_free(value);
}

void fibonacci_dijkstra_gmp(mpz_t f, int n)
{
    if (n < 2)
        return mpz_set_si(f, n);
    GHashTable *hash = g_hash_table_new(g_direct_hash, g_direct_equal);

    mpz_ptr p0 = g_malloc(sizeof(mpz_t));
    mpz_init_set_si(p0, 0);
    mpz_ptr p1 = g_malloc(sizeof(mpz_t));
    mpz_init_set_si(p1, 1);

    g_hash_table_insert(hash, GINT_TO_POINTER(0), p0);
    g_hash_table_insert(hash, GINT_TO_POINTER(1), p1);
    mpz_ptr v = _fib(hash, n);
    mpz_set(f, v);
    g_hash_table_foreach(hash, _free, NULL);
    g_hash_table_destroy(hash);
}
