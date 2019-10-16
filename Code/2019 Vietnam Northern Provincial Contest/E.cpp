#include <bits/stdc++.h>

using namespace std;

long long a[4], n;

double f(double x, int sign) {
    double now = 1, ans = 0;
    for (int i = 0; i <= n; ++i) {
        ans += a[i] * now;
        now *= x;
    }
    return ans * sign;
}
#define esp 1e-6

bool Solve2(double l, double r, int sign, long long &ans) {
    for (int loop = 0; loop < 200; ++loop) {
        double m = (l + r) / 2;
        if (f(m, sign) <= 0) {
            l = m;
        } else r = m;
    }
    long long x = l;
    if (abs(f(x - 1, sign)) <= esp ) { ans = min(ans, x - 1); return 1; }
    if (abs(f(x, sign)) <= esp ) { ans = min(ans, x); return 1; }
    if (abs(f(x + 1, sign)) <= esp) {ans = min(ans, x + 1); return 1; }
    return 0;
}

bool Solve(double ll, double rr, int sign, long long &ans) {
    double l = ll, r = rr;
    for (int loop = 0; loop < 200; ++loop) {
        double m1 = (l + l + r) / 3, m2 = (l + r + r) / 3;
        if (f(m1, sign) < f(m2, sign)) {
            l = m1;
        } else r = m2;
    }
    Solve2(ll, l, sign, ans);
    Solve2(l, rr, sign * -1, ans);
}
void Solve() {
    cin >> n;
    for (int i = n; i >= 0; --i) cin >> a[i];
    if (a[n] < 0) for (int i = 0; i <= n; ++i) a[i] *= -1;
    if (n == 1) {
        cout << -a[0] / a[1] << '\n';
    }
    else if (n == 2) {
        long long b = a[1], c = a[0];
        long long delta = b * b - 4ll * a[2] * c;
        long long x = sqrt(delta);
        if (x * x < delta) ++x;
        if (x * x > delta) --x;
        cout << (-b  - x) / (2ll * a[2]) << '\n';
    } else {
        long long ans = 1e18;
        double uon = -1.0 * a[2] / (3ll * a[3]);
        Solve(-1e9, uon, 1, ans);
        Solve(uon, 1e9, -1, ans);
        cout << ans << '\n';
    }
}
int main()
{
    //ios::sync_with_stdio(false); cin.tie(NULL);
    int test; cin >> test;
    while (test--) Solve();
}
