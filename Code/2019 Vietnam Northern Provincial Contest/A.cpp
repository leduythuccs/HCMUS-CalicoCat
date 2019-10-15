#include <bits/stdc++.h>

using namespace std;
#define long long long
const int N = 1e5 + 100;
int x[N], t[N];
long f[N];
vector<int> Rank;
const int CACHE_SIZE = 1 << 23;

struct TPersistentSegmentTree{
    struct Node {
        int cnt = 0;
        long sum = 0;
        Node * lc = nullptr, *rc = nullptr;
    } cache[CACHE_SIZE], *it = cache, * root[N];

    void reset() {
        //--it;
        while (true) {
            it -> cnt = it -> sum = 0;
            it  -> lc = it -> rc = nullptr;
            if (it == cache) break;
            --it;
        }
        //it = cache;
        root[0] = new Node();
    }

    inline int GetCnt(Node * node) { return node ? node -> cnt : 0; }
    inline long GetSum(Node * node) { return node ? node -> sum : 0; }
    inline Node * GetLeft(Node * node) { return node ? node -> lc : nullptr; }
    inline Node * GetRight(Node * node) { return node ? node -> rc : nullptr; }
    
    Node * Update(Node * cur, int l, int r, int u, int x) {
        //cerr << l << ' ' << r << ' ' << u << ' ' << x << '\n';
        if (l > u || r < u) return cur;
        if (l == r) {
            it -> cnt = GetCnt(cur) + 1;
            it -> sum = GetSum(cur) + x;
            it -> lc = it -> rc = nullptr;
            return it++;
        }
        int m = (l + r) >> 1;
        Node * ret = it++;
        ret -> lc = Update(GetLeft(cur), l, m, u, x);
        ret -> rc = Update(GetRight(cur), m + 1, r, u, x);
        ret -> sum = GetSum(ret -> lc) + GetSum(ret -> rc);
        ret -> cnt = GetCnt(ret -> lc) + GetCnt(ret -> rc);
        return ret;
    }

    long Query(Node * cur, int l, int r, int k) {
        // Pick sum of first k elements
        //cerr << l << ' ' << r << ' ' << GetCnt(cur) << ' ' << k << '\n';
        if (GetCnt(cur) == k) return GetSum(cur);
        if (l == r) {
            if (GetCnt(cur) >= k) return 1ll * Rank[l] * k;
        }
        int m = (l + r) >> 1;
        if (GetCnt(GetLeft(cur)) >= k) return Query(GetLeft(cur), l, m, k);
        return GetSum(GetLeft(cur)) + Query(GetRight(cur), m + 1, r, k - GetCnt(GetLeft(cur)));
    }
}PIT;

int p[N];
void Solve() {
    int n;
    cin >> n;
    PIT.reset();
    Rank.clear();
    for (int i = 1; i <= n; ++i) {
        f[i] = 1e18;
        cin >> x[i] >> t[i];
        Rank.push_back(t[i]);
    }
    sort(Rank.begin(), Rank.end());
    Rank.resize(unique(Rank.begin(), Rank.end()) - Rank.begin());
    for (int i = 1; i <= n; ++i) {
        int p = lower_bound(Rank.begin(), Rank.end(), t[i]) - Rank.begin();
        PIT.root[i] = PIT.Update(PIT.root[i - 1], 0, Rank.size(), p, t[i]);
    }
    auto Cost = [&](int pos, int pick) {
        //cerr << "Cost " << pos << ' ' << pick << '\n';
        return PIT.Query(PIT.root[pos], 0, Rank.size(), pick) + (long)x[pos];
    };
    vector<pair<int, pair<int, int> > > opt;
    opt.push_back({1, {1, 1}});
    for (int i = 2; i <= n; ++i) {
        while (opt.size() && Cost(opt.back().first, opt.back().second.first) >= Cost(i, opt.back().second.first)) opt.pop_back();
        if (opt.empty()) {
            opt.push_back({i, {1, i}});
            continue;
        }
        int l = opt.back().second.first + 1, r = opt.back().second.second, cur = opt.back().second.second + 1;
        int id = opt.back().first;
        while (l <= r) {
            int m = (l + r) >> 1;
          //  cerr << i << ' ' << id << ' ' << m << '\n'; 
            if (Cost(id, m) >= Cost(i, m)) {
                cur = m;
                r = m - 1;
            } else l = m + 1;
        }
        opt.back().second.second = cur - 1;
        if (cur != i + 1) opt.push_back({i, {cur, i}}); 
        //cerr << "Back now: " << opt.back().first << ' ' << opt.back().second.first << ' ' << opt.back().second.second << '\n';
    }
    for (auto x : opt) {
        for (int i = x.second.first; i <= x.second.second; ++i) f[i] = Cost(x.first, i); 
    }
    //for (int i = 1; i <= n; ++i) cout << f[i] << " \n"[i == n];
    int q; cin >> q;
    while (q--) {
        long x;
        cin >> x;
        cout << upper_bound(f + 1, f + n + 1, x) - f - 1 << " \n"[!q];
    }
}

int main() {
    //double stime = clock();
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int test; cin >> test;
    while (test--) Solve();
    //cerr << "Time: " << (clock() - stime) / CLOCKS_PER_SEC * 1000 << "ms.\n";
}