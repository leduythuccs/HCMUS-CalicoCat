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
    int n, c;
    cin >> n >> c;
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        int m = s[0] - '0';
        int sec = s[2] - '0';
        sec = sec * 10 + s[3] - '0';
        sec = sec + m * 60;
        sum += sec;
    }
    sum -= (n - 1) * c;
    int minute = sum / 60;
    int sec = sum % 60;
    int hour = minute / 60;
    minute %= 60;
    cout << out(hour) << ':' << out(minute) << ':' << out(sec);
//{
//    long long n1, n2, n12;
//    cin >> n1 >> n2 >> n12;
//    cout << (n1 + 1) * (n2 + 1) / (n12 + 1) - 1;
    return 0;
}
