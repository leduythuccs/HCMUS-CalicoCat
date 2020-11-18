#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
string a[maxn];
vector<int> d[maxn];
int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};
int n, m;
void solve() {
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        d[i].resize(m);
        for (int j = 0; j < m; ++j)
            d[i][j] = -1;
    }
    deque<pair<int, int> > q;
    for (int i = 0; i < n; ++i)
        if (a[i][0] != '@') {
            int cost = (a[i][0] == '.');
            if (cost)
                q.push_back({i, 0});
            else
                q.push_front({i, 0});
            d[i][0] = cost;
        }
    for (int i = 0; i < m; ++i)
        if (a[n - 1][i] != '@' && d[n - 1][i] == -1) {
            int cost = (a[n - 1][i] == '.');
            if (cost)
                q.push_back({n - 1, i});
            else
                q.push_front({n - 1, i});
            d[n - 1][i] = cost;
        }
    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop_front();
        int du = d[x][y];
        if (x == 0 || y == m - 1) {
            cout << du << '\n';
            return;
        }
        for (int i = 0; i < 8; ++i) {
            int xx = x + dx[i], yy = y + dy[i];
            if (xx < 0 || yy < 0 || xx >= n || yy >= m) continue;
            if (d[xx][yy] != -1 || a[xx][yy] == '@') continue;
            int cost = (a[xx][yy] == '.');
            if (cost) {
                q.push_back({xx, yy});
            }
            else {
                q.push_front({xx, yy});
            }
            d[xx][yy] = du + cost;
        }
    }
    cout << -1 << '\n';
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    while (true) {
        cin >> n >> m;
        if (n == 0 && m == 0) {
            break;
        }
        solve();
    }
    return 0;
}
