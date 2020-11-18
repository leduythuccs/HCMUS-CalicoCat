#include <bits/stdc++.h>
using namespace std;
int n, k;
int l[20];
vector<int> h;
long long calc() {
    long long res = 0;
    int M = 0;
    for (int i = 0; i < n; ++i) {
        l[i] = M;
        M = max(M, h[i]);
    }
    int maxRight = 0;
    for (int i = n - 1; i >= 0; --i) {
        res += max(0, min(l[i], maxRight) - h[i]);
        maxRight = max(maxRight, h[i]);
    }
    return res;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    cin >> n >> k;
    h.resize(n);
    for (int i = 0; i < n; ++i)
        cin >> h[i];
    long long res = 0;
    for (int i = 0; i < n; ++i)
        for (int j = i; j < n; ++j)
            for (int i3 = j; i3 < n; ++i3)
                for (int x = 0; x <= k; ++x)
                    for (int y = 0; y <= k - x; ++y) {
                        int z = k - x - y;
                        h[i] += x;
                        h[j] += y;
                        h[i3] += z;
                        res = max(res, calc());
                        h[i] -= x;
                        h[j] -= y;
                        h[i3] -= z;
                    }
    cout << res;
    return 0;
}
