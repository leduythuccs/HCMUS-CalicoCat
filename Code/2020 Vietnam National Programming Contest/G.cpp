#include <bits/stdc++.h>
using namespace std;
const int maxU = 5e5 + 5;
const int maxn = 1e5 + 5;
vector<int> uoc[maxU];
vector<int> num[maxU];
vector<pair<int, int> > adj[maxn];
vector<pair<int, long long> > newAdj[maxn];
int h[maxn];
long long d[maxn];
int lab[maxn];
int t_in[maxn], t_out[maxn], _time;
int RMQ[18][maxn * 2];
int n;
vector<int> euler;
void DFS(int u, int p = -1) {
    t_in[u] = ++_time;
    euler.push_back(u);
    for (auto x : adj[u]) {
        int v = x.first, w = x.second;
        if (v == p) continue;
        d[v] = d[u] + w;
        h[v] = h[u] + 1;
        DFS(v, u);
        ++_time;
        euler.push_back(u);
    }
    t_out[u] = _time;
}
bool isAnc(int u, int v) {
    return t_in[u] < t_in[v] && t_out[v] < t_out[u];
}
int LCA(int u, int v) {
    if (isAnc(u, v)) return u;
    if (isAnc(v, u)) return v;
    if (t_out[u] > t_in[v]) swap(u, v);
    int l = t_out[u], r = t_in[v];
    int k = log2(r - l + 1);
    int h1 = h[RMQ[k][l]];
    int h2 = h[RMQ[k][r - (1 << k) + 1]];
    if (h1 < h2)
        return RMQ[k][l];
    return RMQ[k][r - (1 << k) + 1];
}
void initRMQ() {
    for (int i = 1; i <= _time; ++i)
        RMQ[0][i] = euler[i];
    for (int j = 1; (1 << j) <= _time; ++j)
        for (int i = 1; i + (1 << j) - 1 <= _time; ++i) {
            int h1 = h[RMQ[j - 1][i]];
            int h2 = h[RMQ[j - 1][i + (1 << (j - 1))]];
            if (h1 < h2)
                RMQ[j][i] = RMQ[j - 1][i];
            else RMQ[j][i] = RMQ[j - 1][i + (1 << (j - 1))];
        }
}
bool cmp(int u, int v) {
    return t_in[u] < t_in[v];
}
long long current_res;
long long calc(int u) {
    long long fi = 0, se = 0;
    for (auto x : newAdj[u]) {
        int v = x.first;
        long long dif = calc(v) + x.second;
        if (dif > fi) se = fi, fi = dif;
        else if (dif > se) se = dif;
    }
    current_res = max(current_res, fi + se);
    return fi;
}
long long solve(vector<int> &spec) {
    if (spec.size() == 0) return 0;
    sort(spec.begin(), spec.end(), cmp);
    int k = spec.size();
    for (int i = 0; i < k - 1; ++i) {
        spec.push_back(LCA(spec[i], spec[i + 1]));
    }
    sort(spec.begin(), spec.end(), cmp);
    spec.erase(unique(spec.begin(), spec.end()), spec.end());
    vector<int> st;
    current_res = 0;
    for (int v : spec) {
        while (st.size() && !isAnc(st.back(), v)) st.pop_back();
        if (st.size() == 0) {
            st.push_back(v);
            continue;
        }
        int u = st.back();
        newAdj[u].push_back({v, d[v] - d[u]});
        st.push_back(v);
    }
    calc(st[0]);
    for (int v : spec)
        newAdj[v].clear();
    return current_res;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int cur = 500000;
#ifdef LOCAL
    cur = 100;
#endif // LOCAL
    for (int i = 1; i <= cur; ++i)
        for (int j = i; j <= cur; j += i)
            uoc[j].push_back(i);
    while (true) {
        cin >> n;
        if (n == 0) break;
        _time = 0;
        euler.clear();
        euler.push_back(0);
        for (int i = 1; i <= n; ++i) {
            adj[i].clear();
        }
        vector<int> to_do;
        for (int i = 1; i <= n; ++i) {
            cin >> lab[i];
            for (int x : uoc[lab[i]]) {
                num[x].push_back(i);
                if (num[x].size() == 1)
                    to_do.push_back(x);
            }
        }

        for (int i = 2; i <= n; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        DFS(1);
        initRMQ();
        long long res = 0;
//        cout << LCA(7, 6) << '\n';
//        return 0;
        for (int x : to_do) {
            res = max(res, solve(num[x]) * x);
        }
        cout << res << '\n';
        //clear
        for (int x : to_do)
            num[x].clear();
    }
    return 0;
}
