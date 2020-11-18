#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
int cnt;
vector<bool> vs;
vector<vector<int> > adj;
void DFS(int u) {
    vs[u] = 1;
    ++cnt;
    for (int v : adj[u]) if (!vs[v]) {
        DFS(v);
    }
}
int solve() {
    int n;
    cin >> n;
    vector<pair<pair<int, int>, int> > p(n), q(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].first.first >> p[i].first.second;
        q[i] = {{p[i].first.second, p[i].first.first}, i};
        p[i].second = i;
    }
    vector<int> nxtX(n), nxtY(n);
    sort(p.begin(), p.end());
    for (int i = 0; i < n; ++i) {
        if (i + 1 < n && p[i].first.first == p[i + 1].first.first)
            nxtY[p[i].second] = p[i + 1].second;
        else
            nxtY[p[i].second] = -1;
    }
    sort(q.begin(), q.end());
    for (int i = 0; i < n; ++i) {
        if (i + 1 < n && q[i].first.first == q[i + 1].first.first)
            nxtX[q[i].second] = q[i + 1].second;
        else
            nxtX[q[i].second] = -1;
    }
    vector<bool> noiX(n), noiY(n);
    adj.assign(n, vector<int>());
    for (int i = 0; i < n; ++i) {
        int id = p[i].second;
        if (!noiX[id]) {
            int nxt = nxtX[id];
            if (nxt == -1) {
                return !(cout << "NO");
            }
            noiX[id] = noiX[nxt] = true;
            adj[id].push_back(nxt);
            adj[nxt].push_back(id);
        }
        if (!noiY[id]) {
            int nxt = nxtY[id];
            if (nxt == -1) {
                return !(cout << "NO");
            }
            noiY[id] = noiY[nxt] = true;
            adj[id].push_back(nxt);
            adj[nxt].push_back(id);
        }
    }
    for (int i = 0; i < n; ++i)
        if (adj[i].size() != 2)
            return !(cout << "NO");
    cnt = 0;
    vs.clear();
    vs.resize(n, false);
    DFS(0);
    if (cnt != n)
        return !(cout << "NO");
    cout << "YES";
    return 0;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int t;
    cin >> t;
    while (t--) {
        solve();
        cout << '\n';
    }
    return 0;
}
