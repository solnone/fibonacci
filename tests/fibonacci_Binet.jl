#!/usr/bin/env julia
# Binet's Formula
# export JULIA_NUM_THREADS=3
# println("JULIA_NUM_THREADS=",Threads.nthreads())

function main()
  line = readline()
  n::Int = tryparse(Int, line)
  n < 0 && error("The input value must be a positive integer")
  n > 358 && setprecision(ceil(Int, log(2, 10)* n))
  sqrt5 = √ BigFloat(5)
  a = Threads.@spawn ((1+sqrt5)/2)^n
  b = Threads.@spawn ((1-sqrt5)/2)^n
  println(round(BigInt, (sqrt5/5)*(fetch(a)-fetch(b))))
end

main()
