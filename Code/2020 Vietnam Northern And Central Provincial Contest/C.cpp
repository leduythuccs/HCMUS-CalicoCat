#include <iostream>

using namespace std;
bool check(int u) {
    if (u <= 1) return false;
    if (u == 2) return true;
    for (int i = 2; i * i <= u; ++i)
            if (u % i == 0) return false;
    return true;
}
int getsum(int n) {
    int res = 0;
    while (n) {
        res += n % 10;
        n /= 10;
    }
    return res % 10;
}
int main()
{
    int m, n;
    while (cin >> m >> n) {
        int res = 0;
        for (; n; ++m) {
            if (!check(m)) continue;
            --n;
            if (getsum(m) == 0) {++res;}
        }
        cout << res << '\n';
    }
    return 0;
}
