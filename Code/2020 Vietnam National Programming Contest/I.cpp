#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e6 + 10;
const int MOD = 1e9 + 7;
long long p[maxn], rev[maxn];
long long f[maxn];
long long C(int k, int n) {
    return p[n] * rev[k] % MOD * rev[n - k] % MOD;
}
long long fastPow(long long x, long long n) {
    long long res = 1;
    for (; n; n >>= 1, x = x * x % MOD)
        if (n & 1)
            res = res * x % MOD;
    return res;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    p[0] = 1;
    int n = 2000005;
    for (int i = 1; i <= n; ++i)
        p[i] = p[i - 1] * i % MOD;
    rev[n] = fastPow(p[n], MOD - 2);
    for (int i = n - 1; i >= 0; --i)
        rev[i] = rev[i + 1] * (i + 1) % MOD;
    f[0] = 0; f[1] = 1;
    for (int i = 2; i <= n; ++i)
        f[i] = (f[i - 1] + f[i - 2]) % MOD;
    int x, y;
    cin >> x >> y;
    if (x == 0) return !(cout << f[y]);
    if (y == 0) return !(cout << f[x]);
    long long res = 0;
    for (int i = 1; i <= x; ++i) {
        int dx = x - i;
        int dy = y - 1;
        res = (res + f[i] * C(dx, dx + dy)) % MOD;
    }

    for (int i = 1; i <= y; ++i) {
        int dx = x - 1;
        int dy = y - i;
        res = (res + f[i] * C(dx, dx + dy)) % MOD;
    }
    cout << res;
    return 0;
}
