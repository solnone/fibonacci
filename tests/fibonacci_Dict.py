#!/usr/bin/env python3
dic = {0:0, 1:1}
def fib(n):
  if n in dic:
      return dic[n]

  m = n >> 1
  if (n % 2 == 0):
      dic[n]=fib(m)*((fib(m-1) << 1)+fib(m))
  else:
      dic[n]=fib(m+1)**2 + fib(m)**2
  return dic[n]

line = input()
try:
    n = int(line)
except ValueError:
    n = -1

if (n < 0):
    print("The input value must be a positive integer")
else:
    print(fib(n))
