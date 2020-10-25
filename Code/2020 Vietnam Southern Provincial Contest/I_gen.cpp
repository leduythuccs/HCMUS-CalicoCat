#include <bits/stdc++.h>

using namespace std;

int randInt(int n) { return (rand() * (RAND_MAX + 1) + rand()) % n; }
int randInt(int l, int r) { return randInt(r - l + 1) + l; }

int main()
{
    while (true) {
        int n = 5;
        string s(n, '0');
        for (int i = 0; i < n; ++i)
            if (rand() % 3 == 0)
                s[i] = '*';
            else
                s[i] = (rand() % 3) + 'a';
        ofstream inp("input.txt");
        inp << s;
        n = rand() % 100 + 1;
        s = string(n, '0');
        for (int i = 0; i < n; ++i)
            s[i] = (rand() % 3) + 'a';
        inp << '\n' << s;
        inp.close();
        system("python I_trau.py < input.txt > output.txt");
        system("I.exe < input.txt > output.ans");
        ifstream outf("output.txt");
        ifstream ansf("output.ans");
        if (system("fc output.txt output.ans") != 0) {
            cout << "Wrong answer!\n";
            return 0;
        }
        cout << "Correct!\n";
    }
    return 0;
}
