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

    public static int answerQuery(int l, int r) {
        long left_pairs = 0;
        long odd = 0;
        long denom = 1;

        for (int c = 0; c < 26; c++) {
            int cnt = prefixCnt[c][r] - prefixCnt[c][l - 1];
            left_pairs += cnt / 2;
            if ((cnt & 1) == 1) odd++;
            denom = (denom * fact[cnt / 2]) % MOD;
        }

        long res = fact[(int)left_pairs] * modinv(denom) % MOD;
        if (odd > 0) res = (res * odd) % MOD;

        return (int)res;
    }    
}


public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        String s = bufferedReader.readLine();

        Result.initialize(s);

        int q = Integer.parseInt(bufferedReader.readLine().trim());

        IntStream.range(0, q).forEach(qItr -> {
            try {
                String[] firstMultipleInput = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

                int l = Integer.parseInt(firstMultipleInput[0]);

                int r = Integer.parseInt(firstMultipleInput[1]);

                int result = Result.answerQuery(l, r);

                bufferedWriter.write(String.valueOf(result));
                bufferedWriter.newLine();
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        });

        bufferedReader.close();
        bufferedWriter.close();
    }
}

