#include <iostream>

using namespace std;

const int N = 1e5 + 100;
int f[11111];
pair<int, int> p[N];
int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> p[i].second >> p[i].first;
        int ret = 0;
        int timeNow = 0;
        f[p[i].second] += p[i].first;
        for (int j = 1; j <= 10000; ++j) {
            timeNow += f[j];
            ret = max(ret, timeNow - j);
        }
        cout << ret << '\n';
    }
}
