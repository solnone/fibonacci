#!/usr/bin/env python3
#
# Fast doubling Fibonacci algorithm (Python)
#
# Copyright (c) 2015 Project Nayuki
# All rights reserved. Contact Nayuki for licensing.
# https://www.nayuki.io/page/fast-fibonacci-algorithms
# https://funloop.org/post/2017-04-14-computing-fibonacci-numbers.html
#

# (Public) Returns F(n).
def fibonacci(n):
    """ Calculate the Nth Fibonacci number using the doubling method. """
    if n <= 0:
        return 0
    else:
        return _fib(n-1)[1]

# (Private) Returns the tuple (F(n), F(n+1)).
def _fib(n):
    """ Calculate Nth Fibonacci number using the doubling method. Return the
    tuple (F(n), F(n+1))."""
    if n == 0:
        return (0, 1)
    else:
        a, b = _fib(n >> 1)
        c = a * ((b << 1) - a)
        d = a * a + b * b
        if n & 1:
            return (d, c + d)
        else:
            return (c, d)

if __name__ == "__main__":
    line = input()
    try:
        n = int(line)
    except ValueError:
        n = 0
    if (n <= 0):
        print(0)
    else:
        print(fibonacci(n))
