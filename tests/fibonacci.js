#!/usr/bin/env node
/*
 * Fast doubling Fibonacci algorithm
 *
 * Copyright (c) 2015 Project Nayuki
 * All rights reserved. Contact Nayuki for licensing.
 * https://www.nayuki.io/page/fast-fibonacci-algorithms
 * https://funloop.org/post/2017-04-14-computing-fibonacci-numbers.html
 *
 */

function _fib(n) {
  if (n == 0) {
    return {a: 0n, b: 1n};
  } else {
    let {a, b} = _fib(n >> 1);
    let c = a*((b * 2n) - a);
    let d = a*a + b*b;
    if (n&1 == 1) {
      return {a: d, b: c+d};
    } else {
      return {a: c, b: d};
    }
  }
}

function fib(n) {
  if (n <= 0) {
    return 0;
  } else {
    let {a, b} = _fib(n-1);
    return b;
  }
}

const readline = require('readline');

const rl = readline.createInterface({
  input: process.stdin
});

rl.question('', (i) => {
  var n = parseInt(i) || -1;
  if (n <= 0) {
    console.log('0');
    return;
  }
  var result = fib(n);
  console.log(`${result}`);
  rl.close();
});


