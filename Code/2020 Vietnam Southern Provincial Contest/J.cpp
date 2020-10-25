#include <bits/stdc++.h>

using namespace std;
const int maxn = 20005;
const int maxm =  40050;
int par[maxn];
int low[maxn], num[maxn], time_DFS;
int root(int u) {
    return par[u] = (par[u] == u ? u : root(par[u]));
}
bool ok(int u, int v) {
    int r1 = root( u);
    int r2 = root(v);
    if (r1 != r2) {
        par[r1] = r2;
        return true;
    }
    return false;
}
int mark[maxm];
int isCrit[maxn];
int belong[maxn], IDBCC;
int cntNode[maxm];
int cntEdge[maxm];
vector<pair<int, int> > edges;
vector<pair<int, int> > adj[maxn];
stack<int> st;
void DFS(int u, int p = -1) {
    low[u] = num[u] = ++time_DFS;
    int cntChild = 0;
    for (auto x : adj[u]) {
        int v = x.first;
        int id = x.second;
        if (id == p) continue;
        if (!num[v]) {
            ++cntChild;
            st.push(id);
            DFS(v, id);
            low[u] = min(low[u], low[v]);
            if (low[v] >= num[u]) {
                isCrit[u] = 1;
//                cerr << "BCC\n";
                ++IDBCC;
                set<int> nodes;
                nodes.insert(u);
                while (true) {
                    int curId = st.top(); st.pop();
//                    cerr << edges[curId].first << ' ' << edges[curId].second << '\n';
                    nodes.insert(edges[curId].first);
                    nodes.insert(edges[curId].second);
                    belong[edges[curId].first] = IDBCC;
                    belong[edges[curId].second] = IDBCC;
                    if (curId == id)
                        break;
                }
                cntNode[IDBCC] = nodes.size();
//                cout << "nodes = " << nodes.size() << ' ' << "edges = " << ed.size() << '\n';
            }
        }
        else {
            low[u] = min(low[u], num[v]);
        }
    }
    if (p == -1)
        isCrit[u] &= (cntChild >= 2);
}
int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        par[i] = i;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        if (u == v) return !(cout << "No");
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        edges.push_back({u, v});
    }
    for (int i = 1; i <= n; ++i)
        sort(adj[i].begin(), adj[i].end());

    for (int i = 1; i <= n; ++i)
        if (num[i] == 0)
            DFS(i);
    for (int i = 0; i < edges.size(); ++i) {
        int u = edges[i].first;
        int v = edges[i].second;
        if (isCrit[u] && isCrit[v]) {
            auto L = lower_bound(adj[u].begin(), adj[u].end(), make_pair(v, 0));
            auto R = lower_bound(adj[u].begin(), adj[u].end(), make_pair(v, m + 1)) - 1;
            int DEM = R - L + 1;
            if (DEM >= 2) return !(cout << "No");
            continue;
        }
        if (isCrit[u]) {
            ++cntEdge[belong[v]];
            continue;
        }
        if (isCrit[v]) {
            ++cntEdge[belong[u]];
            continue;
        }
        assert(belong[u] == belong[v]);
        ++cntEdge[belong[u]];
    }
    for (int i = 1; i <= IDBCC; ++i) {
//        cerr << cntEdge[i] << ' ' <<  cntNode[i] << '\n';
        if (cntEdge[i] > cntNode[i] * 2 - 2)
            return !(cout << "No");
    }
    cout << "Yes";
    return 0;
}
