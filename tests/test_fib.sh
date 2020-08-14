#! /bin/sh
DIR=$(dirname "${0}")
../src/fib 0 370 256 0 0 | sed '1d' | diff - ${DIR}/expected_256.txt && \
../src/fib 0 370 256 0 1 | sed '1d' | diff - ${DIR}/expected_256.txt && \
../src/fib 0 370 0 0 0 | sed '1d' | diff - ${DIR}/expected_256.txt && \
../src/fib 0 370 0 0 1 | sed '1d' | diff - ${DIR}/expected_256.txt