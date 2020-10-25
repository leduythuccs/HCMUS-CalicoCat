#include <bits/stdc++.h>

using namespace std;
string out(int t) {
    stringstream s;
    s << t;
    string ss = s.str();
    if (ss.size() < 2) ss = "0" + ss;
    return ss;
}
int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int t, b;
    cin >> t;
    cin >> b;
    long double len = t / acos(-1); //t/pi
    vector<pair<int, int> > balls(b);
    for (int i = 0; i < b; ++i) {
        cin >> balls[i].second >> balls[i].first;
    }
    sort(balls.begin(), balls.end());
    int res =0 ;
    for (int i = 0; i < b; ++i) {
        int cnt = balls[i].second;
        int r = balls[i].first;
        while (cnt > 0 && len >= r * 2) {
            ++res;
            --cnt;
            len -= r * 2;
        }
    }
    cout << res;
    return 0;
}
