using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Collections;
using System.ComponentModel;
using System.Diagnostics.CodeAnalysis;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.Text.RegularExpressions;
using System.Text;
using System;

class Result
{
    static readonly int MOD = 1000000007;
    static readonly int MAXN = 200000;

    static long[] fact = new long[MAXN + 1];
    static long[] invfact = new long[MAXN + 1];
    static int[,] prefixCnt = new int[26, MAXN + 1];
    static string S;

    static long modpow(long a, long e)
    {
        long r = 1;
        while (e > 0)
        {
            if ((e & 1) == 1) r = (r * a) % MOD;
            a = (a * a) % MOD;
            e >>= 1;
        }
        return r;
    }

    static long modinv(long a) => modpow(a, MOD - 2);


    /*
     * Complete the 'initialize' function below.
     *
     * The function accepts STRING s as parameter.
     */

    public static void initialize(string s)
    {
        S = s;
        int n = s.Length;

        fact[0] = 1;
        for (int i = 1; i <= MAXN; i++) fact[i] = fact[i - 1] * i % MOD;

        invfact[MAXN] = modinv(fact[MAXN]);
        for (int i = MAXN - 1; i >= 0; i--) invfact[i] = invfact[i + 1] * (i + 1) % MOD;

        for (int c = 0; c < 26; c++) prefixCnt[c, 0] = 0;
        for (int i = 0; i < n; i++)
        {
            for (int c = 0; c < 26; c++) prefixCnt[c, i + 1] = prefixCnt[c, i];
            prefixCnt[s[i] - 'a', i + 1]++;
        }
    }


    /*
     * Complete the 'answerQuery' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts following parameters:
     *  1. INTEGER l
     *  2. INTEGER r
     */

    public static int answerQuery(int l, int r)
    {
        long left_pairs = 0;
        long odd = 0;
        long denom = 1;

        for (int c = 0; c < 26; c++)
        {
            int cnt = prefixCnt[c, r] - prefixCnt[c, l - 1];
            left_pairs += cnt / 2;
            if ((cnt & 1) == 1) odd++;
            denom = (denom * fact[cnt / 2]) % MOD;
        }

        long ways = fact[left_pairs] * modinv(denom) % MOD;
        if (odd > 0) ways = (ways * odd) % MOD;

        return (int)ways;
    }
}


class Solution
{
    public static void Main(string[] args)
    {
        TextWriter textWriter = new StreamWriter(@System.Environment.GetEnvironmentVariable("OUTPUT_PATH"), true);

        string s = Console.ReadLine();

        Result.initialize(s);

        int q = Convert.ToInt32(Console.ReadLine().Trim());

        for (int qItr = 0; qItr < q; qItr++)
        {
            string[] firstMultipleInput = Console.ReadLine().TrimEnd().Split(' ');

            int l = Convert.ToInt32(firstMultipleInput[0]);

            int r = Convert.ToInt32(firstMultipleInput[1]);

            int result = Result.answerQuery(l, r);

            textWriter.WriteLine(result);
        }

        textWriter.Flush();
        textWriter.Close();
    }
}
