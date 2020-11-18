#include <bits/stdc++.h>
using namespace std;
struct Point {
    long long x, y;
};
long long area(const Point &A, const Point &B, const Point &C) {
    long long S = (A.x - B.x) * (A.y + B.y) + (B.x - C.x) * (B.y + C.y) + (C.x - A.x) * (C.y + A.y);
    if (S > 0) S = 1;
    if (S < 0) S = -1;
    return S;
}
bool intersect(const Point &A, const Point &B, const Point &C, const Point &D) {
    //A B khac phia C D
    bool ok1 = area(C, D, A) * area(C, D, B) < 0;
    //C D khac phia AB
    bool ok2 = area(A, B, C) * area(A, B, D) < 0;
    return ok1 && ok2;
}
bool check(const Point &A, const Point &B, const Point &C, const Point &D) {
    //AB
    bool ok1 = intersect(A, B, C, D);
    bool ok2 = intersect(A, C, B, D);
    bool ok3 = intersect(A, D, B, C);
    return ok1 || ok2 || ok3;
}
Point p[55];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    int n;
    while (true) {

        cin >> n;
        if (n == 0) break;
        for (int i = 0; i < n; ++i) {
            cin >> p[i].x >> p[i].y;
        }
        int cnt = 0;
        for (int i = 0; i < n - 3; ++i)
            for (int j = i + 1; j < n - 2; ++j)
                for (int k = j + 1; k < n - 1; ++k)
                    for (int z = k + 1; z < n; ++z)
                        cnt += check(p[i], p[j], p[k], p[z]);
        cout << cnt << '\n';
    }
    return 0;
}
