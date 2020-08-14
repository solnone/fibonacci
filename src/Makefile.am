bin_PROGRAMS=fib fib_iterative_gmp fib_doubling_gmp fib_doubling_mixing fib_doubling_gmp_cpp fib_recursion_gmp_cpp main

fib_SOURCES=fib.c fibonacci.c fibonacci_io.c
fib_LDADD=

fib_doubling_gmp_SOURCES=fib_doubling_gmp.c fibonacci_gmp.c fibonacci_io.c

fib_doubling_mixing_SOURCES=fib_doubling_mixing.c fibonacci.c fibonacci_gmp.c fibonacci_io.c


fib_iterative_gmp_SOURCES=fib_iterative_gmp.c fibonacci_gmp.c fibonacci_io.c

fib_doubling_gmp_cpp_SOURCES=fib_doubling_gmp_cpp.cpp fibonacci_gmp.c
fib_doubling_gmp_cpp_LDADD=-lgmpxx $(fib_doubling_gmp_cpp_LIBS)

fib_recursion_gmp_cpp_SOURCES=fib_recursion_gmp_cpp.cpp
fib_recursion_gmp_cpp_LDADD=-lgmpxx $(fib_recursion_LIBS)

main_SOURCES=main.c fibonacci.c fibonacci_gmp.c fibonacci_dijkstra_gmp.c fibonacci_io.c
main_CFLAGS=@GLIB_CFLAGS@
main_LDADD=@GLIB_LIBS@ $(fibonacci_LIBS)

include_HEADERS=clock_time.h fibonacci.h fibonacci_gmp.h ui256.h fibonacci_dijkstra_gmp.h fibonacci_io.h
