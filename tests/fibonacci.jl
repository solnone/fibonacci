#!/usr/bin/env julia
#
# Fast doubling Fibonacci algorithm
#
# Copyright (c) 2015 Project Nayuki
# All rights reserved. Contact Nayuki for licensing.
# https://www.nayuki.io/page/fast-fibonacci-algorithms
# https://funloop.org/post/2017-04-14-computing-fibonacci-numbers.html
#

function _fib(n::Int)
  if n == 0
    return big(0), big(1)
  else
    a, b = _fib(n >> 1)
    c = a*((b << 1) - a)
    d = a^2 + b^2
    if n&1 == 1
      return d, c+d
    else
      return c, d
    end
  end
end

function fib(n::Int)
  if n <= 0
    return big(0)
  else
    return _fib(n-1)[2]
  end
end

function main()
  n::Int = tryparse(Int, readline())
  println(fib(n))
end

main()
