#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        long long x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        long long dx = abs(x2 - x1), dy = abs(y2 - y1);
        cout << max(dx, dy) * 2 - (dx % 2 != dy % 2) << '\n';
    }
    return 0;
}
