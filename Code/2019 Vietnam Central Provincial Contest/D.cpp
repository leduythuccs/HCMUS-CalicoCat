#include <iostream>

using namespace std;

const int N = 1e5 + 100;
int BIT[N * 5], a[N], isPrime[N * 10];

void Up(int u) { for(; u < N * 5; u += u & -u) BIT[u]++;}
int Get(int u) {
    int ans = 0;
    for(; u > 0; u -= u & -u) ans += BIT[u];
    return ans;
}

void Eratos() {
    for (int i = 2; i < 10 * N; ++i) isPrime[i] = 1;
    for (int i = 2; i < 10 * N; ++i) {
        for (long long j = 1ll * i *i; j < N * 10; j += i) isPrime[j] = 0;
    }
}
int main()
{
    Eratos();
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        a[i] = isPrime[x] + a[i - 1];
    }
    Up(N);
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += Get(2 * a[i] - i + N);
    //    cerr << a[i] << ' ' << Get(2 * a[i] - i + N) << '\n';
        Up(2 * a[i] - i + N);
    }
    cout << ans;
}
