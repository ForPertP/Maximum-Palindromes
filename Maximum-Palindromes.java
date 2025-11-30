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


    static final int MOD = 1000000007;
    static final int MAXN = 200000;

    static long[] fact = new long[MAXN + 1];
    static long[] invfact = new long[MAXN + 1];
    static int[][] prefixCnt = new int[26][MAXN + 1];
    static String S;
