#include <bits/stdc++.h>

using namespace std;
const int N = 333;
int a[N][N];
struct Edge {
    int u, v;
    long long c;
    void read() {
        cin >> u >> v >> c;
        a[u][v] = a[v][u] = 1;
    }
}edge[11111];


const int MOD = 1e9;
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) a[i][j] = 1e9;
        a[i][i] = 0;
    }
    for (int i = 0; i < m; ++i) {
        edge[i].read();
    }
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
            }
        }
    }
    long long res = 0;
    bool flag = false;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            if (a[u][v] == 1e9) continue;
            long long ans = 1e18;
            for (int i = 0; i < m; ++i) {
                ans = min(ans, edge[i].c * (1 + a[edge[i].u][u] + a[edge[i].v][v]));
                ans = min(ans, edge[i].c * (1 + a[edge[i].u][v] + a[edge[i].v][u]));
            }
            //cerr << u << ' ' << v << ' ' << ans << '\n';
            if (res + ans >= MOD) flag = true;
            res = (res + ans) % MOD;
        }
    }
    if (flag) cout << setw(9) << setfill('0');
    cout << res;
}
