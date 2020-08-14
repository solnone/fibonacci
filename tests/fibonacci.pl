#!/usr/bin/perl -w
#
# Fast doubling Fibonacci algorithm
#
# Copyright (c) 2015 Project Nayuki
# All rights reserved. Contact Nayuki for licensing.
# https://www.nayuki.io/page/fast-fibonacci-algorithms
# https://funloop.org/post/2017-04-14-computing-fibonacci-numbers.html
#

use bignum;
use strict;

sub _fib {
  my($n) = @_;
  if ($n == 0) {
    return (0, 1);
  } else {
    ($a, $b) = _fib($n >> 1);
    my $c = $a*(($b << 1) - $a);
    my $d = $a**2 + $b**2;
    if ($n & 1) {
      return ($d, $c+$d);
    } else {
      return ($c, $d)
    }
  }
}

sub fib {
  my($n) = @_;
  if (0 == $n) {
    return 0;
  } else {
    ($a, $b) = _fib($n-1);
    return $b;
  }
}

my $n = <STDIN>;
chomp($n);
if ($n =~ /^\d+?$/) {
  print fib($n), "\n";
} else {
  print "0\n";
}
