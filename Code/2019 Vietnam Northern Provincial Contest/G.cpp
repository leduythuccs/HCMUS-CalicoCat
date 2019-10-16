#include <bits/stdc++.h>

using namespace std;

const int MAXN = 4096;
const int N = 1010;

bitset<MAXN> bs[N][N];
string st[N];
void Solve() {
    int n, m;
    cin >> m >> n;
    m = n = 1000;
    for (int i = 0; i < m; ++i) st[i].assign(n, '0');
    //for (int i = 0; i < m; ++i) cin >> st[i];
    bs[m - 1][n - 1].reset();
    for (int i = m - 1; i >= 0; --i) {
        for (int j = n - 1; j >= 0; --j) {
            bs[i][j].reset();
            if (i == m - 1 && j == n - 1) {
                bs[m - 1][n - 1][st[m - 1][n - 1] - '0'] = 1;
                continue;
            }
            if (i != m - 1) {
                bs[i][j] |= (bs[i + 1][j]);
            }
            if (j != n - 1) bs[i][j] |= bs[i][j + 1];
            bs[i][j] <<= (st[i][j] - '0');
        }
    }
    bool first = true;
    for (int i = 0; i < MAXN; ++i) if (bs[0][0][i]) {
        if (!first) cout << ' ';
        cout << i;
        first = false;
    }
    cout << '\n';
}
int main() {
//    ios::sync_with_stdio(false); cin.tie(NULL);
    int test;
    cin >> test;
    while (test--) Solve();
}
