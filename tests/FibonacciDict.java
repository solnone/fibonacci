import java.math.BigInteger;
import java.util.*;

public final class FibonacciDict {

  final static Map<Integer, BigInteger> map =
      new HashMap<Integer, BigInteger>();
  static {
    map.put(0, BigInteger.ZERO);
    map.put(1, BigInteger.ONE);
  }

  public static BigInteger fib(final int n) {
    BigInteger v = map.get(n);
    if (v == null) {
      final int m = n >> 1;
      final BigInteger mv = fib(m);
      if (n % 2 == 0) {
        v = mv.multiply(fib(m - 1).multiply(BigInteger.TWO).add(mv));
      } else {
        v = fib(m + 1).pow(2).add(mv.pow(2));
      }
      map.put(n, v);
    }
    return v;
  }

  public static void main(final String[] args) {
    try (final Scanner s = new Scanner(System.in)) {
      final int n = s.nextInt();
      if (n >= 0) {
        System.out.println(FibonacciDict.fib(n));
      }
    }
  }
}