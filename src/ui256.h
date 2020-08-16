#pragma once
#include <stddef.h>
#include <stdint.h>
#ifdef __MACH__
#include <string.h>
#else
/*
 * fls: find last (most-significant) bit set.
 * Note fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.
 */
static __inline__ int fls(unsigned int x)
{
    return 32 - __builtin_clz(x);
}
#endif
typedef uint64_t u64;
typedef unsigned __int128 u128;
struct uint256 {
    u128 low, high;
};
typedef struct uint256 u256;

union union_mixing256 {
    u64 ui64;
    u128 ui128;
    u256 ui256;
};

struct mixing {
    union union_mixing256 a, b;
};

static inline void ui256_set_si(u256 *out, __int128 l)
{
    out->low = l;
    out->high = l < 0 ? -1 : 0;
}

static inline void ui256_set_ui(u256 *out, u128 l)
{
    out->low = l;
    out->high = 0;
}

static inline void ui256_set(u256 *out, u256 *v)
{
    out->low = v->low;
    out->high = v->high;
}

static inline void ui256_add_ui(u256 *out, u128 y)
{
    out->low += y;
    out->high += (out->low < y);
}

static inline void ui256_add(u256 *out, u256 *x, u256 *y)
{
    out->low = x->low + y->low;
    out->high = x->high + y->high + (out->low < y->low);
}

static inline void ui256_sub(u256 *out, u256 *x, u256 *y)
{
    u256 c = {.low = ~y->low, .high = ~y->high};
    ui256_add_ui(&c, 1);
    out->low = x->low + c.low;
    out->high = x->high + c.high + (out->low < c.low);
}

/*
 * References https://github.com/chenshuo/recipes/blob/master/basic/int128.h
 */
static inline void ui256_mul(u256 *out, u128 x, u128 y)
{
    u64 a = x;  // & 0xFFFFFFFFFFFFFFFF;
    u64 c = x >> 64;
    u64 b = y;  // & 0xFFFFFFFFFFFFFFFF;
    u64 d = y >> 64;
    /*
    if (b == 0 && d == 0) {
        out->low = a*c;
        out->high = 0;
        return ;
    }
    */
    u128 ab = (u128) a * b;
    u128 bc = (u128) b * c;
    u128 ad = (u128) a * d;
    u128 cd = (u128) c * d;

    out->low = ab + (bc << 64);
    out->high = cd + (bc >> 64) + (ad >> 64) + (out->low < ab);
    out->low += (ad << 64);
    out->high += (out->low < (ad << 64));
}

static inline void ui256_divrem(u256 *quot, u128 *rem, u256 *x, u128 y)
{
    u64 hh = (x->high >> 64);
    u128 hl = (x->high) & 0xFFFFFFFFFFFFFFFF;
    u128 lh = (x->low >> 64);
    u128 ll = (x->low) & 0xFFFFFFFFFFFFFFFF;

    u128 qhh = hh / y;
    u128 mhh = hh % y;

    if (mhh != 0) {
        hl += (mhh << 64);
    }

    u128 qhl = hl / y;
    u128 mhl = hl % y;

    if (mhl != 0) {
        lh += (mhl << 64);
    }

    u128 qlh = lh / y;
    u128 mlh = lh % y;

    if (mlh != 0) {
        ll += (mlh << 64);
    }

    u128 qll = ll / y;
    *rem = ll % y;

    quot->high = (qhh << 64) + qhl;
    quot->low = (qlh << 64) + qll;
}
