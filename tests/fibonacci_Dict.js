#!/usr/bin/env node
var dict = { 0: 0n, 1: 1n };
function fib(n) {
  if (n in dict) {
    return dict[n];
  }
  var m = n >> 1;
  if (n % 2 == 0) {
    dict[n] = fib(m) * (2n * fib(m - 1) + fib(m));
  } else {
    dict[n] = fib(m + 1) ** 2n + fib(m) ** 2n;
  }
  return dict[n];
}

const readline = require('readline');

const rl = readline.createInterface({
  input: process.stdin
});

rl.question('', (i) => {
  var n = parseInt(i) || -1;
  if (n < 0) {
    console.log('The input value must be a positive integer');
    return;
  }
  var result = fib(n);
  console.log(`${result}`);
  rl.close();
});

