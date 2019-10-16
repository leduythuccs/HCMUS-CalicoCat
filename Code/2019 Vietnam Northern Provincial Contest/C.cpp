#include <iostream>

#define long long long

using namespace std;

const int N = 100 + 2;

int m, n, p;
int spd[N], st[N];
long due[N];
bool useless[N];
bool done[N];

bool check(long en)
{
    for (int i = 0; i < m; ++i) {
        due[i] = en;
        useless[i] = false;
    }
    for (int i = 0; i < n; ++i) done[i] = false;
    int work = 0;
    while (true) {
        int proj = -1;
        for (int i = 0; i < m; ++i)
            if (!useless[i] && (proj == -1 || due[i] > due[proj]
                || (due[i] == due[proj] && spd[i] > spd[proj]))) {
                proj = i;
            }
        if (proj == -1) return false;
        int pack = -1;
        for (int i = 0; i < n; ++i) {
            long tc = due[proj] - spd[proj];
            if (!done[i] && st[i] <= tc && (pack == -1 || st[i] > st[pack])) {
                pack = i;
            }
        }
        if (pack == -1) {
            useless[proj] = true;
            continue;
        }
        ++work;
        due[proj] -= spd[proj];
        done[pack] = true;
        if (work == n) return true;
    }
    return false;
}

int main()
{
    cin >> m >> n >> p;
    for (int i = 0; i < m; ++i) {
        cin >> spd[i];
        spd[i] = (p + spd[i] - 1) / spd[i];
    }
    for (int i = 0; i < n; ++i) cin >> st[i];

    long lo = 1, hi = 1e12, ans = 0;
    while (lo <= hi) {
        long mid = (lo + hi) / 2;
        if (check(mid)) ans = mid, hi = mid - 1;
        else lo = mid + 1;
    }
    cout << ans - 1;
    return 0;
}
