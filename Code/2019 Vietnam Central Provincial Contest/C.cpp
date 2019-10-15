#include <iostream>
#include <algorithm>

using namespace std;

int tests;

int gcd(int x, int y)
{
    x = abs(x), y = abs(y);
    if (x == 0) return y;
    if (y == 0) return x;
    return __gcd(x, y);
}

int main()
{
    cin >> tests;
    while (tests--) {
        int x, y, z, t;
        cin >> x >> y >> z >> t;
        cout << (gcd(x, y) == gcd(z, t) ? "YES" : "NO") << '\n';
    }
    return 0;
}
