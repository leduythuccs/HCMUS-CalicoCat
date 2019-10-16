
#include <bits/stdc++.h>

using namespace std;

#define long long long

typedef pair <long, int> II;

const int N = 1e5 + 10;

int n, k, lim, RSize = 0;
int a[N];

long R[N];

II operator + (const II &A, const II &B) {
    return II(A.first + B.first, A.second + B.second);
}

struct Fenwick {
    int n;
    II fw[N];
    void Init(int _n) {
        n = _n;
        for (int i = 1; i <= n; ++i) fw[i] = II(0, 0);
    }
    void UpdateLeft(int i, II v) {
        for (i; i > 0; i -= i & -i) fw[i] = fw[i] + v;
    }
    void UpdateRight(int i, II v) {
        for (i; i <= n; i += i & -i) fw[i] = fw[i] + v;
    }
    II QueryLeft(int i) {
        II ans = II(0, 0);
        for (i; i > 0; i -= i & -i) ans = ans + fw[i];
        return ans;
    }
    II QueryRight(int i) {
        II ans = II(0, 0);
        for (i; i <= n; i += i & -i) ans = ans + fw[i];
        return ans;
    }
} FT[2];

void Compress() {
    RSize = 0;
    for (int i = 1; i <= n; ++i) R[++RSize] = a[i];
    sort(R + 1, R + RSize + 1); RSize = unique(R + 1, R + RSize + 1) - (R + 1);
    for (int i = 0; i < 2; ++i)
        FT[i].Init(RSize);
}

int Pos(long v) {
    return upper_bound(R + 1, R + RSize + 1, v) - R - 1;
}

bool Ok(long groups) {
    int pos = Pos(groups);
    II les = FT[0].QueryLeft(pos);
    II big = FT[1].QueryRight(pos + 1);
    long sum = les.first + 1LL * big.second * groups;
    return sum >= groups * k;
}

void Solve() {
    for (int i = 1; i <= lim; ++i) {
        int val = a[i], pos = Pos(val);
        FT[0].UpdateRight(pos, II(val, +1));
        FT[1].UpdateLeft(pos, II(val, +1));
    }
    for (int i = lim + 1; i <= n; ++i) {
        int val = a[i], pos = Pos(val);
        FT[0].UpdateRight(pos, II(val, +1));
        FT[1].UpdateLeft(pos, II(val, +1));
        long l = 0, r = (long)1e14 + 2, f = 0;
        while (l <= r) {
            long m = (l + r) >> 1;
            if (Ok(m)) {
                f = m;
                l = m + 1;
            } else r = m - 1;
        }
        cout << f << ' ';
    }
    cout << '\n';
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL);
    int TC; cin >> TC;
    while (TC--) {
        cin >> n >> k >> lim;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        Compress();
        Solve();
    }
    return 0;
}
