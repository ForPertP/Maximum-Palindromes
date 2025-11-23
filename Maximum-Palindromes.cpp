#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

// From https://www.hackerrank.com/challenges/maximum-palindromes/forum

const int MOD = 1000000007;
long long int I[101010];
long long int F[101010];
int chars[26][101010];

long long int fexp(long long int a, long long int b)
{
    if (b ==0)
        return 1LL;
    
    long long int res = fexp(a, b/2);
    res = (res * res) % MOD;
    if (b % 2 == 1)
        res = (res * a) % MOD;

    return res;
}

long long int inv(long long int a)
{
    return fexp(a, MOD-2);
}

void initialize(string s)
{
    F[0] = 1;
    for (int i = 1; i <= 100000; ++i)
        F[i] = (F[i-1] * i) % MOD;
    
    for (int i = 0; i <= 100000; ++i)
        I[i] = inv(F[i]);
        
    for(int i = 1; i <= s.length(); ++i)
    {
        int p = i;
        int c = s[p-1]-'a';
        while (p <= 100000)
        {
            chars[c][p] += 1;
            p += p & (-p);
        }
    }
}

int query(int p, int c)
{
    int sum = 0;
    while (p > 0)
    {
        sum += chars[c][p];
        p -= p & (-p);
    }
    
    return sum;
}

int query(int l,int r, int c)
{
    return query(r, c) - query(l-1, c);
}

long long int answerQuery(int l, int r)
{
    int c_odd = 0;
    int c_even = 0;
    long long int res = 1;

    for (int c = 0; c < 26; ++c)
    {
        int q_range = query(l, r, c);
        if (q_range%2 == 1)
            c_odd++;
        
        res = (res * I[q_range/2]) % MOD;
        c_even += q_range / 2;
    }
    
    if (c_even == 0 && c_odd == 0)
        return 0LL;
    
    res = (res * F[c_even]) % MOD;
    if (c_odd > 0)
        res = (res * c_odd) % MOD;
    
    return res;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    initialize(s);

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++)
    {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int l = stoi(first_multiple_input[0]);
        int r = stoi(first_multiple_input[1]);

        int result = answerQuery(l, r);
        fout << result << "\n";
    }

    fout.close();

    return 0;
}



string ltrim(const string &str)
{
    string s(str);
    s.erase(
        s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) { return !isspace(ch); })
    );
    return s;
}

string rtrim(const string &str)
{
    string s(str);
    s.erase(
        find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !isspace(ch); }).base(), s.end()
    );
    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
