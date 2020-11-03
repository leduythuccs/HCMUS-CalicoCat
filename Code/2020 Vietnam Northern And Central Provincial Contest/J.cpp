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
        return 0;
    }
};
const int maxn = 1e5 + 5;
vector<pair<int, int> > adj[maxn];
long long d[maxn];
int cntInside[maxn], cap[maxn], saveEdge[maxn * 20];
void dijkstra(int s) {
    memset(d, 63, sizeof(d));
    priority_queue<pair<long long, int>, vector<pair<long long, int> > , greater<pair<long long, int> > > heap;
    d[s] = 0;
    heap.push({0, s});
    while (heap.size()) {
        auto tmp = heap.top(); heap.pop();
        int u = tmp.second;
        long long du = tmp.first;
        if (du != d[u]) continue;
        for (auto x : adj[u]) {
            int v = x.first, w = x.second;
            if (d[v] > du + w) {
                d[v] = du + w;
                heap.push({d[v], v});
            }
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int n, m, K;
    cin >> n >> m >> K;
    for (int i = 1; i <= m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }

    int nNode = 2 + n + K;
    int s = 0;
    int t = n + K + 1;
    MaxFlow flow(nNode);
    for (int i = 1; i <= n; ++i)
        flow.addEdge(K + i, t, 1);
    vector<tuple<long long, int, int> > edges;
    for (int i = 1; i <= K; ++i) {
        int spec;
        cin >> spec >> cap[i];
        flow.addEdge(s, i, cap[i]);
        dijkstra(spec);
        for (int u = 1; u <= n; ++u)
            if (d[u] != d[0]) {
                edges.push_back(make_tuple(d[u], i, u));
                flow.addEdge(i, u + K, 1);
                saveEdge[edges.size() - 1] = flow.e.size() - 2;
            }
    }
    sort(edges.begin(), edges.end());
    vector<long long> cost;
    for (int i = 0; i <edges.size(); ++i)
        cost.push_back(get<0>(edges[i]));
    cost.erase(unique(cost.begin(), cost.end()), cost.end());
    auto check = [&](long long c) {
        for (auto &ed : flow.e)
            ed.flow = 0;
        for (int i = 0; i < edges.size(); ++i) {
            if (get<0>(edges[i]) <= c)
                flow.e[saveEdge[i]].cap = 1;
            else {
                flow.e[saveEdge[i]].cap = 0;
            }
        }
        return flow.maxflow(s, t) == n;
    };
    int l = 0;
    int r = cost.size() - 1;
    int res = 0;
    while (l <= r) {
        int mid =  (l + r) >> 1;
        if (check(cost[mid]))
            res = cost[mid], r = mid - 1;
        else l = mid + 1;
    }
    cout << res;
    return 0;
}
