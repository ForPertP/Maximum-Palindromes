#include <bits/stdc++.h>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

static const int MOD  = 1000000007;
static const int MAXN = 200000;

long long fact[MAXN + 1];
long long invfact[MAXN + 1];
int prefixCnt[26][MAXN + 1];
string S;

long long modpow(long long a, long long e) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

long long modinv(long long a) {
    return modpow(a, MOD - 2);
}

/* initialize */
void initialize(string s) {
    S = s;

    int n = s.size();
    fact[0] = 1;

    for (int i = 1; i <= MAXN; i++)
        fact[i] = fact[i - 1] * i % MOD;

    invfact[MAXN] = modinv(fact[MAXN]);

    for (int i = MAXN - 1; i >= 0; i--)
        invfact[i] = invfact[i + 1] * (i + 1) % MOD;

    for (int c = 0; c < 26; c++)
        prefixCnt[c][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int c = 0; c < 26; c++)
            prefixCnt[c][i + 1] = prefixCnt[c][i];

        prefixCnt[s[i] - 'a'][i + 1]++;
    }
}

/* answerQuery */
int answerQuery(int l, int r) {
    int freq[26];

    for (int c = 0; c < 26; c++)
        freq[c] = prefixCnt[c][r] - prefixCnt[c][l - 1];

    long long left_pairs = 0;
    long long odd        = 0;
    long long denom      = 1;

    for (int c = 0; c < 26; c++) {
        left_pairs += freq[c] / 2;
        if (freq[c] % 2 == 1) odd++;
        denom = denom * fact[freq[c] / 2] % MOD;
    }

    long long ways = fact[left_pairs] * modinv(denom) % MOD;
    if (odd > 0) ways = (ways * odd) % MOD;

    return (int)ways;
}


int main() {
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    initialize(s);

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input =
            split(rtrim(first_multiple_input_temp));

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

std::vector<string> split(const string &str)
{
    vector<string> tokens;
    string_view str_view(str);
    size_t start = 0;
    size_t end = 0;

    while ((end = str_view.find(' ', start)) != string_view::npos)
    {
        if (end > start)
        {
            tokens.emplace_back(str_view.substr(start, end - start));
        }
        start = end + 1;
    }

    if (start < str_view.size())
    {
        tokens.emplace_back(str_view.substr(start));
    }

    return tokens;
}
