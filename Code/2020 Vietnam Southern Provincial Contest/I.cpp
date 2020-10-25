#include <bits/stdc++.h>

using namespace std;
const int maxN = 200005;
const int maxM = 105;
int R[maxN][maxM], L[maxN][maxM];
inline void optimizeL(int &L, int val) {
    if (L == 0 || (L != 0 && L > val))
        L = val;
}
inline void optimizeR(int &R, int val) {
    if (R < val) R = val;
}
int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    string P, S;
    cin >> P >> S;
    int n = S.length();
    int m = P.length();
    int p = -1;
    for (int i = 0; i < m; ++i)
        if (P[i] == '*') {
            p = i;
            break;
        }
    string SAVE = "";
    if (p != -1) {
        SAVE = P.substr(0, p);
        P = P.substr(p);
    }
    else {
        if (S.length() != P.length()) return !(cout << 0);
    }
    m = P.length();
    S = " " + S + S;
    int res = 0;
    for (int i = 1; i <= 2 * n; ++i) {
        optimizeR(R[i][0], i);
        for (int j = 0; j < m; ++j) {
            if (R[i][j] != 0) {
                if (P[j] == '*') {
                    optimizeR(R[i + 1][j], R[i][j]);
                    optimizeR(R[i + 1][j + 1], R[i][j]);
                    optimizeR(R[i][j + 1], R[i][j]);
                }
                else if (P[j] == S[i]) {
                    optimizeR(R[i + 1][j + 1], R[i][j]);
                }
            }
        }
        int pos = i - n;
        if (pos >= 1 && R[i][m] != 0)
            if (pos <= R[i][m]) {
                if (pos + SAVE.length() > R[i][m]) continue;
                if (S.substr(pos, SAVE.length()) == SAVE)
                    ++res;
            }
    }
    cout << res;
    return 0;
}
