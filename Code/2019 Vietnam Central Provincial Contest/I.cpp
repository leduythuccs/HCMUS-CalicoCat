#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 100;

int RMQ[N][18], a[N], lg[N];
map<int, long long> g;

int GCD(int l, int r) {
    int d = lg[r - l + 1];
    return __gcd(RMQ[l][d], RMQ[r - (1 << d) + 1][d]);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n;
    cin >> n;
    for (int i = 2; i <= n; ++i) lg[i] = lg[i / 2] + 1;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) RMQ[i][0] = a[i];
    for (int j = 1; j < 18; ++j) for (int i = 1; i + (1 << j) - 1<= n; ++i)
        RMQ[i][j] = __gcd(RMQ[i][j - 1], RMQ[i + (1 << (j - 1))][j - 1]);
    for (int i = 1; i <= n; ++i) {
        int x = a[i], bef = i - 1;
        while (bef < n) {
            int ri = bef + 1;
            for (int j = 17; j >= 0; --j) if (ri + (1 << j) <= n)
                if (GCD(i, ri + (1 << j)) == x) {
                    ri += 1 << j;
                }
            g[x] += ri - bef;
            bef = ri;
            x = __gcd(x, a[ri + 1]);
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int x; cin >> x;
        cout << g[x] << '\n';
    }
}
