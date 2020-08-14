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
  a = big(1)
  b = big(1)
  count = 63 - leading_zeros(n)
  mask = 1 << count
  for i = 1:count
    mask >>= 1
    c = a*((b << 1) - a)
    d = a^2 + b^2
    if (n & mask) != 0
      a = d
      b = c + d
    else
      a = c
      b = d
    end
  end
  return a, b
end

function fib(n::Int)
  if n < 2
    return big(n)
  else
    return _fib(n-1)[2]
  end
end

function main()
  n::Int = tryparse(Int, readline())
  println(fib(n))
end

main()
