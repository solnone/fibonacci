import java.math.BigInteger;
import java.util.*;

public final class Fibonacci {

  public static BigInteger fib(final int k) {
    if (k < 2) {
      return BigInteger.valueOf(k);
    }
    final int n = k - 1;
    final int count = Integer.SIZE - Integer.numberOfLeadingZeros(n) - 1;
    int mask = 1 << count;
    BigInteger a = BigInteger.ONE, b = BigInteger.ONE;
    for (int i = 0; i < count; i++) {
      mask >>= 1;
      BigInteger c = a.multiply(b.multiply(BigInteger.TWO).subtract(a));
      BigInteger d = a.pow(2).add(b.pow(2));
      if ((n & mask) != 0) {
        a = d;
        b = c.add(d);
      } else {
        a = c;
        b = d;
      }
    }
    return b;
  }

  public static void main(final String[] args) {
    try (final Scanner s = new Scanner(System.in)) {
      final int n = s.nextInt();
      System.out.println(Fibonacci.fib(n));
    }
  }
}