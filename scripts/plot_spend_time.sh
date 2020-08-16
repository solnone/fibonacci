#!/bin/sh
DIR=$(dirname "${0}")

mkdir -p plot
src/fib -e 93  -b 64  -t -m doubling 1> /dev/null 2> plot/fib_doubling_64.dat
src/fib -e 93  -b 64  -t -m iterative 1> /dev/null 2> plot/fib_iterative_64.dat
src/fib -e 186 -b 128 -t -m doubling 1> /dev/null 2> plot/fib_doubling_128.dat
src/fib -e 186 -b 128 -t -m iterative 1> /dev/null 2> plot/fib_iterative_128.dat
src/fib -e 370 -b 256 -t -m doubling 1> /dev/null 2> plot/fib_doubling_256.dat
src/fib -e 370 -b 256 -t -m iterative 1> /dev/null 2> plot/fib_iterative_256.dat
src/fib -e 370 -b 0   -t -m doubling 1> /dev/null 2> plot/fib_doubling_mixing.dat
src/fib -e 370 -b 0   -t -m iterative 1> /dev/null 2> plot/fib_iterative_mixing.dat
src/fib_doubling_gmp 0 400 0 1 0 1> /dev/null 2> plot/fib_doubling_gmp.dat
src/fib_doubling_mixing 0 400 0 1 0 1> /dev/null 2> plot/fib_doubling_gmp_mixing.dat
LC_CTYPE=en_US.UTF-8 gnuplot ${DIR}/spend_time.gp
XDG_OPEN=$(which xdg-open)
if [ $? -ne 0 ]; then
    XDG_OPEN=$(which open)
    if [ $? -ne 0 ]; then
      XDG_OPEN=$(which file)
    fi
fi
$XDG_OPEN plot/spend_time.png
