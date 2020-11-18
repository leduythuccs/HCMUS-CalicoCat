#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 5;
vector<pair<int, int> > adj[maxn];
long long longest[maxn];
pair<long long, int> far1[maxn], far2[maxn], far3[maxn];
long long res;
int n;
void DFS(int u, int p = -1) {
    longest[u] = 0;
    far1[u] =  {0, u};
    far2[u] = far3[u] = {0, 0};
    for (auto x : adj[u]) {
        int v = x.first, w = x.second;
        if (v == p) continue;
        DFS(v, u);
        pair<long long, int> cur = far1[v];
        cur.second = v;
        cur.first += w;
        if (cur.first > far1[u].first)
            far3[u] = far2[u],
            far2[u] = far1[u],
            far1[u] = cur;
        else if (cur.first > far2[u].first)
            far3[u] = far2[u],
            far2[u] = cur;
        else if (cur.first > far3[u].first)
            far3[u] = cur;
        longest[u] = max(longest[u], longest[v]);
    }
    longest[u] = max(longest[u], far1[u].first + far2[u].first);
}
void re_DFS(int u, int p = -1, long long far_from_home = 0, long long longest_from_home = 0) {
    vector<pair<long long, int> > f;
    for (auto x : adj[u]) if (x.first != p)
        f.push_back({longest[x.first], x.first});
    sort(f.rbegin(), f.rend());
    for (auto x : adj[u]) {
        int v = x.first, w = x.second;
        if (v == p) continue;
        //cut canh (u, v)
        long long fi = far1[u].first;
        long long se = far2[u].first;
        if (far1[u].second == v)
            fi = far3[u].first;
        if (far2[u].second == v)
            se = far3[u].first;
        if (fi < se) swap(se, fi);
        if (far_from_home > fi)
            se = fi,
            fi = far_from_home;
        else if (far_from_home > se)
            se = far_from_home;
        long long cur_long = max(longest_from_home, fi + se);
        for (int i = 0; i < f.size(); ++i) {
            if (f[i].second != v) {
                cur_long = max(cur_long, f[i].first);
                break;
            }
        }
        res = min(res, abs(longest[v] - cur_long));
        re_DFS(v, u, fi + w, cur_long);

    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    while (true) {
        cin >> n;
        if (n == 0) break;
        for (int i = 1; i <= n; ++i)
            adj[i].clear();
        for (int i = 2; i <= n; ++i) {
            int p, w;
            cin >> p >> w;
            adj[p].push_back({i, w});
            adj[i].push_back({p, w});
        }
        res = 1e18;
        DFS(1);
        re_DFS(1);
        cout << res << '\n';
    }
    return 0;
}
