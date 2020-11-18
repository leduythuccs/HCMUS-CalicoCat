#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int n, k;
    cin >> n >> k;
    if (n <= 2)
        return !(cout << "NO");
    int t = 1;
    while ((t + 1) * t <= n - 1) ++t;
    int x = min(n - 1 - (n - 1) / t, n - t);
    if (k > x) return !(cout << "NO");
    cout << "YES\n";
    for (int i = 1; i <= k; ++i)
        cout << i << ' ' << i + t << '\n';
    for (int i = 1; i <= n && k > 0; ++i) {
        if (i % t == 0) continue;
        cout << i << ' ' << i + 1 << '\n';
        --k;
    }
    return 0;
}
