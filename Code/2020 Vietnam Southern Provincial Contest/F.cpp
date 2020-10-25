#include <bits/stdc++.h>

using namespace std;
string normalize(string a) {
    string res;
    for (char c : a)
        if ('a' <= c && c <= 'z')
            res.push_back(c);
        else if ('A' <= c && c <= 'Z')
            res.push_back(c);
    return res;
}
void Zfunc(vector<int> &a, vector<int> &Z) {
    int n = a.size() - 1;
    //base 1
    int l = -1, r = -1;
    for (int i = 2; i <= n; ++i) {
        if (i <= r)
            Z[i] = min(r - i + 1, Z[i - l + 1]);
        while (i + Z[i] <= n && a[Z[i] + 1] == a[i + Z[i]]) ++Z[i];
        if (i + Z[i] - 1 > r) {
            r = i + Z[i] - 1;
            l = i;
        }
    }
}
const int BASE = 311;
const int MOD = 999999937;
int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int n;
    string S;
    string temp_string;
    while (cin >> temp_string) {
        for (char c : temp_string)
            S.push_back(c);
    }
    S = normalize(S);
    n = S.length();
    assert(n % 2 == 0);
    n /= 2;
    string a = S.substr(0, n);
    string b = S.substr(n);
//    n = 1e6;
//    a = string(n, 'a');
//    b = string(n, 'b');
//    b[0] = 'c';




//    cout << a << '\n' << b << '\n';
    vector<int> C(n + 1);
    for (int i = 0; i < n; ++i) {
        C[i + 1] = b[i] - a[i];
        if (C[i + 1] <= 0) C[i + 1] += 26;
    }
//    for (int i = 1; i <= n; ++i)
//        cout << C[i] << ' ';
//    cout << '\n';
    vector<int> Z(n + 1);
    Zfunc(C, Z);
    Z[1] = n;
    int len_res = n;
    for (int i = 1; i < n; ++i) {
        if (i + 1 + Z[i + 1] - 1 >= n) {
            len_res = i;
            break;
        }
    }
    n = len_res;



    vector<int> newS(n * 2 + 1);
    for (int i = 1; i <= n; ++i)
        newS[i] = newS[i + n] = C[i];
    vector<long long> H(n * 2 + 1), POW(n * 2 + 1);
    POW[0] = 1;
    auto getHash = [&](int l, int r) {
        return (H[r] - H[l - 1] * POW[r - l + 1] + 1ll * MOD * MOD) % MOD;
    };
    auto isLess = [&] (int u1, int v1, int u2, int v2) {
        int l = 1, r = n, res = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (getHash(u1, u1 + mid - 1) == getHash(u2, u2 + mid - 1))
                l = mid + 1, res = mid;
            else r = mid - 1;
        }
        if (res == n) return false;
        return newS[u1 + res] > newS[u2 + res];
    };
    for (int i = 1; i <= n * 2; ++i) {
        H[i] = H[i - 1] * BASE + newS[i];
        H[i] %= MOD;
        POW[i] = POW[i - 1] * BASE % MOD;
    }
    int pos = 1;
    for (int i = 2; i <= n; ++i) {
        if (isLess(pos, pos + n - 1, i, i + n - 1))
            pos = i;
    }
    string ANS;
    for (int i = pos; i <= pos + n - 1; ++i)
        ANS.push_back(newS[i] + 'a' - 1);
    cout << ANS;
    return 0;
}
