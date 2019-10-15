#include <iostream>
#include <iomanip>

using namespace std;

const int N = 100 + 2;

int n;
double a[N], b[N];

double probBifA[N];

bool check(double winProb)
{
    for (int i = 1; i <= n; ++i) {      // score A
        probBifA[i] = 0;
        for (int j = 1; j <= n; ++j) {  // score B
            if (j > i) probBifA[i] += b[j];
            else {
                double cur = (j < i ? 0 : 1 - winProb);
                double sum = 0;
                for (int k = 1; k <= n; ++k) {  // re-roll
                    int score = (j + k <= n ? j + k : j + k - n);
                    if (score > i) sum += b[k];
                    else if (score == i) sum += b[k] * (1 - winProb);
                }
                probBifA[i] += b[j] * max(cur, sum);
            }
        }
    }

//    for (int i = 1; i <= n; ++i) {
//        cerr << setprecision(6) << fixed;
//        cerr << "prob b if a " << i << " = " << probBifA[i] << '\n';
//    }

    double ret = 0;
    for (int i = 1; i <= n; ++i) {  // score A
        double cur = 1 - probBifA[i];
        double sum = 0;
        for (int j = 1; j <= n; ++j) {  // re-roll
            int score = (i + j <= n ? i + j : i + j - n);
            sum += (1 - probBifA[score]) * a[j];
        }
        ret += a[i] * max(cur, sum);
    }
//    cerr << "ret = " << ret << '\n';
    return ret >= winProb;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];

    double lo = 0, hi = 1, ans = 0;
    for (int i = 0; i < 100; ++i) {
        double mid = (lo + hi) / 2;
        if (check(mid)) {
            ans = mid;
            lo = mid;
        }
        else hi = mid;
    }
//    cerr << check(0.5) << '\n';
    cout << setprecision(6) << fixed << ans;
    return 0;
}
