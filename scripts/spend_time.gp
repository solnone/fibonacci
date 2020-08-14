reset
set title "runtime O(n)"
set xlabel "size 400"
set ylabel "time(ns)"
set key left top
set term png enhanced font "Verdana,10"
set output "plot/spend_time.png"
plot [:400][:] \
"plot/fib_doubling_gmp.dat" title "doubling gmp" with linespoints, \
"plot/fib_doubling_gmp_mixing.dat" title "doubling gmp mixing" with linespoints, \
"plot/fib_doubling_mixing.dat" title "doubling mixing" with linespoints, \
"plot/fib_iterative_mixing.dat" title "iterative mixing" with linespoints, \
"plot/fib_doubling_256.dat" title "doubling 256" with linespoints, \
"plot/fib_iterative_256.dat" title "iterative 256" with linespoints, \
"plot/fib_doubling_128.dat" title "doubling 128" with linespoints, \
"plot/fib_iterative_128.dat" title "iterative 128" with linespoints, \
"plot/fib_doubling_64.dat" title "doubling 64" with linespoints, \
"plot/fib_iterative_64.dat" title "iterative 64" with linespoints, \
"plot/fib_doubling_gmp_mixing.dat" title "doubling gmp mixing" with linespoints, \
# "plot/fib_recursion_256.dat" title "recursion 256" with linespoints, \
