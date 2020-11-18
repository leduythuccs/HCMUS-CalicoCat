#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
const int MOD = 1e9 + 7;
int w[maxn];
string s[maxn];
long long p[maxn], rev[maxn];
int cnt[55][26], need[55][26];
long long C(int k, int n) {
    if (k > n || k < 0) return 0;
    return p[n] * rev[k] % MOD * rev[n - k] % MOD;
}
long long fastPow(long long x, long long n) {
    long long res = 1;
    for (; n; n >>= 1, x = x * x % MOD)
        if (n & 1)
            res = res * x % MOD;
    return res;
}
void solve() {


    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> w[i];
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> s[i];
        if (s[i].length() <= 50)
            ++cnt[s[i].length()][s[i][0] - 'A'];
    }
    long long res = 0;
    for (int i = 0; i < m; ++i) if (s[i].length() == n) {
        --cnt[s[i].length()][s[i][0] - 'A'];
        vector<int> to_do;
        for (int j = 0; j < n; ++j) {
            if (need[w[j]][s[i][j] - 'A'] == 0)
                to_do.push_back(j);
            ++need[w[j]][s[i][j] - 'A'];
        }
        long long cur = 1;
        for (int x : to_do) {
            int cnt_need = need[w[x]][s[i][x] - 'A'];
            int cnt_have = cnt[w[x]][s[i][x] - 'A'];
            cur = cur * C(cnt_need, cnt_have) % MOD * p[cnt_need] % MOD;
        }
        for (int x : to_do)
            need[w[x]][s[i][x] - 'A'] = 0;
        res = (res + cur) % MOD;
        ++cnt[s[i].length()][s[i][0] - 'A'];
    }
    for (int i = 0; i < m; ++i) {
        if (s[i].length() <= 50)
            --cnt[s[i].length()][s[i][0] - 'A'];
    }
    cout << res << '\n';
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    p[0] = 1;
    int n = 100005;
    for (int i = 1; i <= n; ++i)
        p[i] = p[i - 1] * i % MOD;
    rev[n] = fastPow(p[n], MOD - 2);
    for (int i = n - 1; i >= 0; --i)
        rev[i] = rev[i + 1] * (i + 1) % MOD;
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
