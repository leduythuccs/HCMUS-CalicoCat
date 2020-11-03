#include <bits/stdc++.h>

using namespace std;
const long long is_query = -7e18;
typedef long long ll;
struct Line {
    ll m, b;
    mutable function<const Line*()> succ;
    bool operator<(const Line & rhs) const {
        if (rhs.b != is_query) return m < rhs.m;
        const Line* s = succ();
        if (!s) return 0;
        ll x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};
struct HullDynamic : public multiset<Line> {
    bool bad(iterator y) {
        auto z = next(y);
        if (y == begin()) {
            if (z == end()) return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == end())
            return y->m == x->m && y->b <= x->b;
        bool A = ((z->m - y->m) < 0);
        bool B = ((y->m - x->m) < 0);
//        assert(A == 0 && B == 0);
//        if (A == B)
//            return (x->b - y->b) * (z->m - y->m) >= (y->b - z->b) * (y->m - x->m);
//        return (x->b - y->b) * (z->m - y->m) >= (y->b - z->b) * (y->m - x->m);
        return 1.0 * (x->b - y->b)  / (y->m - x->m) >= 1.0 * (y->b - z->b) / (z->m - y->m);
    }
    void insert_line(ll m, ll b) {
        auto y = insert({m, b});
        y->succ = [=] {return next(y) == end() ? 0 : &*next(y);};
        if (bad(y)) {
            erase(y); return;
        }
        while (next(y) != end() && bad(next(y)))
            erase(next(y));
        while (y != begin() && bad(prev(y))) erase(prev(y));
    }
    ll eval(ll x) {
        auto l = *lower_bound((Line) {x, is_query});
        return l.m * x + l.b;
    }
};
const int maxn = 1e5 + 5;
int a[maxn];
ll f[maxn], p[maxn];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    srand(time(NULL));
        int n = 100000;
        cin >> n;
        for (int i = 0; i < n; ++i)
            cin >> a[i];
//            a[i] = 1e9;
        HullDynamic hull;
        hull.insert_line(0, 0);
        long long res = a[0];
        for (int i = 0; i < n; ++i) {
            f[i] = 1ll * (n - i) * a[i];
            p[i] = a[i];
            if (i)
                f[i] += f[i - 1], p[i] += p[i - 1];
            res = max(res, hull.eval(n - i - 1) + f[i] - p[i] * (n - i - 1));
            hull.insert_line(p[i], -f[i]);
        }
        cout << res << '\n';
//        long long ans = a[0];
//        auto cost = [&](int l, int r) {
//            if (l == -1)
//                return f[r] - p[r] * (n - r - 1);
//            return (f[r] - f[l]) - (p[r] - p[l]) * (n - r - 1);
//        };
//        for (int i = -1; i < n; ++i)
//            for (int j = i + 1; j < n; ++j)
//                ans = max(ans, cost(i, j));
//        assert(ans == res);
//}
    return 0;
}
