#include <bits/stdc++.h>

using namespace std;
struct Edge {
    int u, v, cap, flow;
};
struct MaxFlow {
    int n, s, t;
    vector<int> d, ptr;
    vector<vector<int> > g;
    vector<Edge> e;
    MaxFlow(int n):n(n),d(n), ptr(n), g(n) {}
    void addEdge(int u, int v, int cap) {
        g[u].push_back(e.size());
        e.push_back({u, v, cap, 0});
        g[v].push_back(e.size());
        e.push_back({v, u, 0, 0});
    }
    int maxflow(int s, int t) {
        this->s = s;
        this->t = t;
        int flow = 0;
        while (bfs()) {
            while (int x = dfs(s, 1e9))
                flow += x;
        }
        return flow;
    }
    bool bfs() {
        queue<int> q;
        for (int i = 0; i < n; ++i) ptr[i] = 0, d[i] = -1;
        d[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int id : g[u]) if (e[id].flow < e[id].cap) {
                int v = e[id].v;
                if (d[v] == -1) {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
        return d[t] != -1;
    }
    int dfs(int u, int flow) {
        if (u == t || flow == 0) return flow;
        for (; ptr[u] < (int) g[u].size(); ++ptr[u]) {
            int id = g[u][ptr[u]];
            int v = e[id].v;
            if (d[v] == d[u] + 1 && e[id].cap > e[id].flow) {
                if (int x = dfs(v, min(flow, e[id].cap - e[id].flow))) {
                    e[id].flow += x;
                    e[id ^ 1].flow -= x;
                    return x;
                }
            }
        }
    }
};


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int T;
    cin >> T;
    while (T--) {
        map<string, int> pro, sub;
        int n, m, k, l;
        cin >> n >> m >> k >> l;
        MaxFlow flow(n + m * 2 + k + 2);
        int s = 0, t = n + m * 2 + k + 1;
        for (int i = 1; i <= l; ++i) {
            int A;
            string B, C;
            cin >> A >> B >> C;
            if (pro.count(B) == 0) {
                int tmp = pro.size();
                pro[B] = tmp + 1;
            }
            if (sub.count(C) == 0) {
                int tmp = sub.size();
                sub[C] = tmp + 1;
            }
            int x = A, y = pro[B], z = sub[C];
            y += n;
            z += n + m * 2;
            flow.addEdge(x, y, 1);
            flow.addEdge(y + m, z, 1);
        }
        for (int i = 1; i <= n; ++i)
            flow.addEdge(s, i, 1);
        for (int i = 1; i <= m; ++i)
            flow.addEdge(n + i, n + m + i, 1);
        for (int i = 1; i <= k; ++i)
            flow.addEdge(n + m + m + i, t, 1);
        cout << flow.maxflow(s, t) << '\n';
    }
    return 0;
}
