#include <bits/stdc++.h>

using namespace std;
const double PI = acos(-1);
int main()
{
    int t;
    cin >> t;
    while (t--) {
        int V;
        cin >> V;
        double res = 3 * pow(2 * PI * V * V, 1 / 3.0);
        cout.precision(6);
        cout << fixed << res << '\n';
    }
    return 0;
}
