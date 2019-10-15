#include <iostream>

using namespace std;

const int N = 55;
int f[N][N];

bool Check(string& st) {
    for (int i = 0; i < (int)st.size(); ++i) {
        for (int j = 2 * i + 1; j < (int)st.size(); ++j){
            if (i == 0) {
                if (st[i] > st[j]) f[i][j] = 0;
                else if (st[i] == st[j]) f[i][j] = 1;
                else f[i][j] = 2;
            } else {
                if (f[i - 1][j - 1] == 2 || st[i] < st[j]) f[i][j] = 2;
                else if (f[i - 1][j - 1] == 1) {
                    if (st[i] > st[j]) f[i][j] = 0;
                    else f[i][j] = 1;
                }
            }
            if (f[i][j] == 0) return false;
        }
    }
    // Check something here
    for (int i = 0; i < (int)st.size(); ++i) {
        for (int j = 2 * i + 1; j < (int)st.size(); ++j) {
            if (j + 1 == (int) st.size()) {
                if (f[i][j] == 1) return false;
            }
        }
    }
    return true;
}

void Solve() {
    string st;
    cin >> st;
    for (int i = (int)st.size() - 1; i >= 0; --i) if (st[i] == '0') {
        string now = st;
        for (int j = i; j < (int)st.size(); ++j) now[j] = '1';
        if (!Check(now)) continue;
        for (int j = i + 1; j < (int)st.size(); ++j) {
            now[j] = '0';
            if (!Check(now)) now[j] = '1';
        }
        cout << now;
        break;
    }
    cout << '\n';
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(NULL);
    int q;
    cin >> q;
    while (q--) Solve();
}
