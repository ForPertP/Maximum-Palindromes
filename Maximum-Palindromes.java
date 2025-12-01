import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.function.*;
import java.util.regex.*;
import java.util.stream.*;
import static java.util.stream.Collectors.joining;
import static java.util.stream.Collectors.toList;

class Result {
    static final int MOD = 1000000007;
    static final int MAXN = 200000;

    static long[] fact = new long[MAXN + 1];
    static long[] invfact = new long[MAXN + 1];
    static int[][] prefixCnt = new int[26][MAXN + 1];
    static String S;

    static long modpow(long a, long e) {
        long r = 1;
        while (e > 0) {
            if ((e & 1) == 1) r = (r * a) % MOD;
            a = (a * a) % MOD;
            e >>= 1;
        }
        return r;
    }

    static long modinv(long a) {
        return modpow(a, MOD - 2);
    }

}
