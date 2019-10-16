#include <algorithm>
#include <iostream>
using namespace std;

const int N = 2555;

long long d[N];
long long f(int i, int j, int k) {
    return d[i] * d[i] + d[j] * d[j] - d[k] * d[k];
}
int main()
{
    int n;
    long long resA = 0, resB = 0, resC = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> d[i];
    sort(d, d + n);
    for (int i = 0; i < n; ++i) {
        int right1 = i + 2, right2 = i + 2, mx = i + 2;
        for (int j = i + 1; j < n - 1; ++j) {
            while (mx < n && d[i] + d[j] > d[mx]) ++mx;
            while (right1 < mx && f(i, j, right1) > 0) ++right1;
            right2 = right1;
            while (right2 + 1 < mx && f(i, j, right2 + 1) == 0) ++right2;
            resA += right1 - j - 1;
            if (right1 < mx && f(i, j, right1) == 0) {
                resB += right2 - right1 + 1;
                resC += mx - right2 - 1;
            } else {
                resC += mx - right1;
            }
            //cerr << i << ' ' << j << ' ' << right1 << ' ' << right2 << ' ' << mx << '\n';
        }
    }
    cout << resA << ' ' << resB << ' ' << resC << '\n';
}
