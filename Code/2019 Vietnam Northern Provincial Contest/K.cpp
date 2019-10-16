#include <bits/stdc++.h>

using namespace std;

const int N = 2020;
int b[N], c[N];
vector<int> e[N];
long long dp[N][N];

void Solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) e[i].clear();
    for (int i = 1; i <= m; ++i) {
        int a;
        cin >> a >> b[i] >> c[i];
        e[a].push_back(i);
    }
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) dp[i][j] = -1;
    }
    dp[0][0] = 0;
    for (int i = 0; i <= n; ++i) {
        for (int j = n; j >= 0; --j) if (dp[i][j] != -1) {
            if (j == i) {
                // Throw customer
                dp[i][0] = max(dp[i][0], dp[i][j]);
            }
          //  cerr << i << ' ' << j << ' ' << dp[i][j] << '\n';
            if (j && j != i) {
                // Go on
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
                // Take another
                for (int k : e[i]) {
                    int nxt = min(b[k], j), nxt2 = max(b[k], j);
                    dp[nxt][nxt2] = max(dp[nxt][nxt2], dp[i][j] + c[k]);
                }
            }
            if (j == 0) {
                // Go on
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
                // Take 1
                for (int k : e[i]) {
                    dp[i + 1][b[k]] = max(dp[i + 1][b[k]], dp[i][j] + c[k]);
                // Take 2
                    for (int z : e[i]) if (z != k) {
                        int nxt = min(b[k], b[z]), nxt2 = max(b[k], b[z]);
                        dp[nxt][nxt2] = max(dp[nxt][nxt2], dp[i][j] + c[z] + c[k]);
                    } else break;
                }
            }
        }
    }
    cout << dp[n][0] << '\n';
}
int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int test;
    cin >> test;
    while (test--) Solve();
}
