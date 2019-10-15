#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 100;
const int MAGIC = 250;

struct Query {
    int l, r, x, y, id;
    void read(int id) {
        cin >> l >> r >> x >> y;
        --l, --r;
        this -> id = id;
    }

    bool operator<(const Query &a) {
        return (l / MAGIC != a.l / MAGIC ? l / MAGIC < a.l / MAGIC : r < a.r);
    }
}query[N];

int res[N], BIT[N], a[N], cnt[N];
void Up(int u, int val) { for(; u < N; u += u & -u) BIT[u]+= val;}
int Get(int u) {
    int ans = 0;
    for(; u > 0; u -= u & -u) ans += BIT[u];
    return ans;
}

void UpMo(int pos) {
    if (cnt[a[pos]]) Up(cnt[a[pos]], -1);
    cnt[a[pos]]++;
    Up(cnt[a[pos]], 1);
}

void DelMo(int pos) {
    Up(cnt[a[pos]], -1);
    cnt[a[pos]]--;
    if (cnt[a[pos]]) Up(cnt[a[pos]], 1);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<int> Rank(n);
    copy(a, a + n, Rank.begin());
    sort(Rank.begin(), Rank.end());
    Rank.resize(unique(Rank.begin(), Rank.end()) - Rank.begin());
    for (int i = 0; i < n; ++i)
        a[i] = lower_bound(Rank.begin(), Rank.end(), a[i]) - Rank.begin();

    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) query[i].read(i);
    sort(query, query + q);
    int l = 0, r = -1;
    for (int i = 0; i < q; ++i) {
        while (r < query[i].r) UpMo(++r);
        while (l > query[i].l) UpMo(--l);
        while (r > query[i].r) DelMo(r--);
        while (l < query[i].l) DelMo(l++);
        res[query[i].id] = Get(query[i].y) - Get(query[i].x - 1);
    }
    for (int i = 0; i < q; ++i) cout << res[i] << '\n';
}
