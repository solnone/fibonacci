#pragma once
#ifdef __MACH__
#include <mach/mach_time.h>
#define CLOCK_TIME u_int64_t
#define CLOCK_GETTIME(x) x = mach_absolute_time()
#define GETTIME(x) x
#else
#include <time.h>
#define CLOCK_TIME struct timespec
#define CLOCK_GETTIME(x) clock_gettime(CLOCK_MONOTONIC, &x)
#define GETTIME(x) (long long) ((x).tv_sec * 1e9 + (x).tv_nsec)
#endif