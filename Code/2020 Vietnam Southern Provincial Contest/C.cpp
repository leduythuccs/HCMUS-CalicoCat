#include <bits/stdc++.h>

using namespace std;
bool nguCheck(long long num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    for (int i = 2; 1ll * i * i <= num; ++i)
        if (num % i == 0)
            return false;
    return true;
}
bool checkPrime(long long num) {
    if (num <= 1) return false;
    if (num == 2 || num == 3) return true;
    if (num % 2 == 0) return false;
    if (num % 3 == 0) return false;
    for (int i = 5; 1ll * i * i <= num + 100; i += 6) {
        if (i == num) break;
        if (num % i == 0) return false;
        if (i + 2 == num) break;
        if (num % (i + 2) == 0) return false;
    }
    return true;
}
int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
//    for (int i = 0; i <= 1000000; ++i)
//        if (nguCheck(i) != checkPrime(i))
//            return !(cout << i);
//    return 0;
    string s;
    cin >> s;
    long long num = 0;
    for (char c : s)
        num = num * 10 + c - '0';

    if (!checkPrime(num))
        return !(cout << "no");

    reverse(s.begin(), s.end());
    num = 0;
    for (char c : s) {
        if (c == '3' || c == '4' || c == '7')
            return !(cout << "no");
        if (c == '6')
            c = '9';
        else if (c == '9')
            c = '6';
        num = num * 10 + c - '0';
    }
    if (!checkPrime(num))
        return !(cout << "no");
    cout << "yes";
    return 0;
}
