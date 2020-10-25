#include <bits/stdc++.h>

using namespace std;
int main() {
#ifdef LOCAL
//    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int a, b;
    cin >> a >> b;
    int f = 1;
    for (int i = a; i <= b; ++i)
        f = f * i % 9;
    cout << f;
    return 0;
}
