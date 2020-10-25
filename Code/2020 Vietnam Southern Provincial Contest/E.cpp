#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 2;

int n;
int a[N];

void place(int i, vector<int> b)
{
    a[i++] = b.back();
    b.pop_back();
    while (b.size() >= 2) {
        a[i + 1] = b.back();
        b.pop_back();
        a[i] = b.back();
        b.pop_back();
        i += 2;
    }
    if (b.size() > 0)
        a[i] = b.back();

    for (int i = 1; i <= n; ++i)
        cout << a[i] << " \n"[i == n];
    exit(0);
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    if (n == 2) {
        if (a[1] == 1)
            cout << "2 1";
        else
            cout << "1 2";
        return 0;
    }

    set<int> s;
    for (int i = n; i >= 1; --i) {
        if (i + 1 < n && *prev(s.end()) > a[i]) {
            // can replace
            int x = *prev(s.end());
            auto it = s.lower_bound(a[i]);
            int y = *it;
            bool can_inc = !((i > 1 && y > a[i - 1]) || next(it) == s.end());
            bool is_dec = (i > 1 && a[i - 1] < a[i]) || (i == 1 && !can_inc);
            if (is_dec) {
//                cerr << "dec " << i << '\n';
                s.erase(it);
                s.insert(a[i]);
                a[i] = y;
                place(i + 1, vector<int>(s.rbegin(), s.rend()));
            }
            else {
                if (!can_inc) {
                    s.insert(a[i]);
                    continue;
                }
//                cerr << "inc " << i  << '\n';
                int z = *next(it);
                s.insert(a[i]);
                s.erase(y);
                a[i] = y;
                a[i + 1] = z;
                s.erase(z);
                place(i + 2, vector<int>(s.rbegin(), s.rend()));
            }
        }
        s.insert(a[i]);
    }
    place(1, vector<int>(s.rbegin(), s.rend()));
    return 0;
}
