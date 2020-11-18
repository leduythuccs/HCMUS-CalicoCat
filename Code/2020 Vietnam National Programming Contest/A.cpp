#include <bits/stdc++.h>
using namespace std;

bool Greater(string M, int day_need, string m_need, int day) {
    return M == m_need && day >= day_need;
}
bool Less(string M, int day_need, string m_need, int day) {
    return M == m_need && day <= day_need;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int day;
        cin >> day;
        string mon;
        cin >> mon;
        mon[0] = mon[0] - 'A' + 'a';
        if (Greater("mar", 21, mon, day) || Less("apr", 20, mon, day))
            cout << "Aries";
        else if (Greater("apr", 21, mon, day) || Less("may", 20, mon, day))
            cout << "Taurus";
        else if (Greater("may", 21, mon, day) || Less("jun", 21, mon, day))
            cout << "Gemini";
        else if (Greater("jun", 22, mon, day) || Less("jul", 22, mon, day))
            cout << "Cancer";
        else if (Greater("jul", 23, mon, day) || Less("aug", 22, mon, day))
            cout << "Leo";
        else if (Greater("aug", 23, mon, day) || Less("sep", 21, mon, day))
            cout << "Virgo";
        else if (Greater("sep", 22, mon, day) || Less("oct", 22, mon, day))
            cout << "Libra";
        else if (Greater("oct", 23, mon, day) || Less("nov", 22, mon, day))
            cout << "Scorpio";
        else if (Greater("nov", 23, mon, day) || Less("dec", 21, mon, day))
            cout << "Sagittarius";
        else if (Greater("dec", 22, mon, day) || Less("jan", 20, mon, day))
            cout << "Capricorn";
        else if (Greater("jan", 21, mon, day) || Less("feb", 19, mon, day))
            cout << "Aquarius";
        else if (Greater("feb", 20, mon, day) || Less("mar", 20, mon, day))
            cout << "Pisces";
        cout << '\n';
    }
    return 0;
}
