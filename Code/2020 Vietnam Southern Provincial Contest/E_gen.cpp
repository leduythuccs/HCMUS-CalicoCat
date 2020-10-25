#include <bits/stdc++.h>

using namespace std;

int randInt(int n) { return (rand() * (RAND_MAX + 1) + rand()) % n; }
int randInt(int l, int r) { return randInt(r - l + 1) + l; }

bool satisfy(vector<int> a)
{
    int n = a.size();
    for (int i = 1; i + 1 < n; ++i)
        if ((a[i - 1] < a[i] && a[i] < a[i + 1]) || (a[i - 1] > a[i] && a[i] > a[i + 1]))
            return false;
    return true;
}

vector<int> gen(int n)
{
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = i + 1;
        swap(a[i], a[randInt(0, i)]);
    }

    vector<int> p, q;
    do {
        if (satisfy(a)) {
            if (p.size() == 0)
                p = a;
            else if (q.size() == 0) {
                q = a;
                break;
            }
        }
        if (!next_permutation(a.begin(), a.end()))
            iota(a.begin(), a.end(), 1);
    }
    while (true);

    ofstream inp("input.txt");
    inp << n << '\n';
    for (int i = 1; i <= n; ++i)
        inp << p[i - 1] << " \n"[i == n];
    return q;
}

int main()
{
    while (true) {
        int n = 11;
        vector<int> ans = gen(n);
        system("E.exe < input.txt > output.txt");
        ifstream outf("output.txt");
        vector<int> out(n);
        for (int i = 0; i < n; ++i)
            outf >> out[i];
        if (!equal(ans.begin(), ans.end(), out.begin())) {
            cout << "Wrong answer!\n";
            return 0;
        }
        cout << "Correct!\n";
    }
    return 0;
}
