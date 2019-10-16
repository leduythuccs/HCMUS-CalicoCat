#include<bits/stdc++.h>

using namespace std;

#define pp pair<int, int>
vector<vector<pp> > v[22];
string a[2];
int main() {
    cin >> a[0] >> a[1];

    for (int i = 1; i <= 21; ++i) v[i].resize((1 << i));
    for (int i = 0; i < a[0].size(); ++i) v[1][a[0][i] - '0'].push_back(pp(i, 0));
    for (int i = 0; i < a[1].size(); ++i) v[1][a[1][i] - '0'].push_back(pp(i, 1));
    a[0] += '~';
    a[1] += '~';
    for (int l = 1; l <= 21; ++l) {
        for (int mask = 0; mask < (1 << l); ++mask) {
  //          cout << "At " << l << ' ' << mask << '\n';
            if (v[l][mask].empty()) {
         //       cout << mask << '\n';
                for (int i = l - 1; i >=0; --i) cout << ((mask >> i) & 1);
                return 0;
            }
            if (l != 21)
            for (pp x : v[l][mask]) {
//                cerr << x.first << ' ' << x.second << ' ' << a[x.second] << '\n';
                for (int j = 0; j < 2; ++j) {
                    if (a[x.second][x.first + 1] - '0' == j) {
                            v[l + 1][(mask << 1) | (j)].push_back({x.first + 1, x.second});
                    }
                }
            }
        }
    }
}
