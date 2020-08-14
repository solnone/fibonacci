#!/usr/bin/env julia
const dict = Dict{Int,BigInt}(0=>BigInt(0), 1=>BigInt(1))

function fib(n::Int)::Any
  get!(dict, n) do
    m::Int = n >> 1
    iseven(n) ? fib(m)*(fib(m-1) << 1 + fib(m)) : fib(m+1)^2 + fib(m)^2
  end
end

function main()
  line = readline()
  n::Int = tryparse(Int, line)
  n < 0 && error("The input value must be a positive integer")
  println(fib(n))
end

main()
