#include <iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        int res = 0;
        for (int i = 1; i <=n; ++i)
        if (k >= i) {
            k -=i ;
            ++res;
        }
        cout << res << '\n';
    }
    return 0;
}
