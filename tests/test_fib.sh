#! /bin/sh
DIR=$(dirname "${0}")
../src/fib -s 0 -e 370 -b 256 -m doubling | sed '1d' | diff - ${DIR}/expected_256.txt && \
../src/fib -s 0 -e 370 -b 256 -m iterative | sed '1d' | diff - ${DIR}/expected_256.txt && \
../src/fib -s 0 -e 370 -m doubling | sed '1d' | diff - ${DIR}/expected_256.txt && \
../src/fib -s 0 -e 370 -m iterative | sed '1d' | diff - ${DIR}/expected_256.txt

