#include <iostream>
#include <vector>
using namespace std;

const int N = 1e6 + 100;
int phi[N];

void Eratos() {
    for (int i = 1; i < N; ++i) phi[i] = i;
    for (int i = 2; i < N; ++i) if (phi[i] == i) {
        for (int j = i; j < N; j += i) phi[j] -= phi[j] / i;
    }
}

int f[N], digit[N];

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL);
    Eratos();
    for (int i = 1; i < N; ++i) {
        digit[i] = digit[i / 10] + 1;
        vector<int> v;
        v.push_back(f[i - 1]);
        v.push_back(f[i - phi[i]]);
        v.push_back(f[i - digit[i]]);
        bool mark[4] = {};
        for (int x : v) if (x < 4) mark[x] = true;
        for (int j = 0; j < 4; ++j) if (!mark[j]) { f[i] = j; break; }
     }
     int q;
    // for (int i = 1; i < 100; ++i) cout << i << ' ' << f[i] << ' ' << phi[i]<< '\n';
     cin >> q;
     while (q--) {
        int x;
        cin >> x;
        cout << (f[x] == 0 ? "KHOA\n" : "BACH\n");
     }
}
