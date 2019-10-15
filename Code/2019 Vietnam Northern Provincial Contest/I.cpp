#include <bits/stdc++.h>

using namespace std;
#define long long long
const long MAX = 1000000000000000;
const int N = 15;

long Count(long r, long w, long k) {
    // Count from 1..r, how many x % w = k
    long ans = r / w;
    if (ans * w + k <= r) ++ans;
    return ans;
}

long Predecessor(long k, long w, long p) {
    // return last x mod w = p and smaller than k
    long x =  (k - 1) / w * w + p;
    if (x >= k) x -= w;
    return x;
}

long g[20], f[20], POW[20];

long Calc(int k, long w, long p) {
    long x = Predecessor(POW[k], w, 0);
    long l = min(p + 1, POW[k] - x);
    return p - l + 1;
}

long nDigit(long w, long p) {
    for (int i = 1; i <= N; ++i) g[i] = f[i] * (p + 1);
    for (int i = 1; i <= N; ++i) {
        long x = Calc(i, w, p);
        g[i] -= x;
        g[i + 1] += x;
    }
    long ret = 0;
    long cnt = 0;
    // for (int i = 1; i <= N; ++i) {
    //     //cout << g[i] << ' '; 
    //     cnt += g[i];
    // }
    // cnt += MAX % w <= p;
    //cout << cnt << '\n';
    for (int i = 1; i <= N; ++i) {
        ret += g[i] * i;
        if (ret > MAX) return MAX + 1;
    }
    ret += (MAX % w <= p ? N + 1 : 0);
    // cerr << "Calc " << p << ' ' << ret << '\n';
    return ret;
}

void Solve() {
    long w, k;
    cin >> w >> k;
    int cnt = 0;
    // for (int i = 0; i < w; ++i) {
    //     for (int x = i; x <= MAX; x += w, ++cnt) cerr << x;
    //     //cerr << cnt << '\n';
    //     //cerr << '\n';
    // }
    // cerr << '\n';
    ++k;
    POW[0] = 1;
    for (int i = 1; i <= N + 1; ++i) POW[i] = POW[i - 1] * 10;  
    for (int i = 1; i <= N; ++i) {
        long l = POW[i - 1], r = min(POW[i], MAX) - 1;
        f[i] = Count(r, w, 0) - Count(l - 1, w, 0);
    }
    f[1]++;
    //for (int i = 0; i < w; ++i) cout << nDigit(w, i) << " \n"[i == w - 1];
    // for (int i = 0; i < w; ++i) nDigit(w, i);
    long l = 0, r = w - 1, cur = 0;
    while (l <= r) {
        long m = (l + r) >> 1;
        if (nDigit(w, m) >= k) {
            cur = m;
            r = m - 1;
        }  else l = m + 1;
    }
    k -= (cur ? nDigit(w, cur - 1) : 0);
    nDigit(w, cur - 1);
    long temp[20] = {};
    for (int i = 1; i <= N; ++i) temp[i] = g[i];
    nDigit(w, cur);
    for (int i = 1; i <= N; ++i) g[i] -= temp[i];
    g[N + 1] = (MAX % w == cur);
    // cout << "Cur = " << cur << ' ' << k << '\n';
    if (cur == 0) {
        g[1]--;
        k--;
    }
    // for (int i = 1; i <= N + 1; ++i) cout << g[i] << " \n"[i == N + 1]; 
    for (int i = 1; i <= N + 1; ++i) {
        if (k > g[i] * i) {
            k -= g[i] * i;
        }  else {
            // 
            // cout << "Go " << i << ' ' << k << '\n';
            long cnt = (k - 1) / i + 1;
            long x = Predecessor(POW[i - 1], w, cur) + w * cnt;
            // cout << "CNT = " << cnt << ", x = " << x << '\n';
            k = i - ((k - 1) % i + 1);
            while (k--) {
                x /= 10;
            }
            cout << x % 10 << '\n';
            return;
        }
    }
}

int main() {
    int test;cin >> test;
    while (test--) Solve();
}