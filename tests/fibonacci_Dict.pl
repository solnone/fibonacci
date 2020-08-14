#!/usr/bin/perl -w
use bignum;
use strict;

my %dic;
$dic{0} = 0;
$dic{1} = 1;

sub fib {
  my($n) = @_;
  if (exists $dic{$n}) {
    return $dic{$n};
  }

  my $m = $n >> 1;
  if (0 == $n % 2) {
    $dic{$n} = fib($m) * ((fib($m - 1) << 1) + fib($m));
  } else {
    $dic{$n} = fib($m + 1)**2 + fib($m)**2;
  }
  return $dic{$n};
}

my $n = <STDIN>;
chomp($n);
if ($n =~ /^\d+?$/) {
  print fib($n), "\n";
} else {
  print "The input value must be a positive integer\n";
}
