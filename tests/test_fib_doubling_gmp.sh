#! /bin/sh
DIR=$(dirname "${0}")
n=9999
test "$(echo $n | ${DIR}/fibonacci.py)" = "$(../src/fib_doubling_gmp $n)" &&
test "218922995834555169026" = "$(../src/fib_doubling_gmp 99)" 