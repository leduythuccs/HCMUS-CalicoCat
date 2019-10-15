#include <bits/stdc++.h>

using namespace std;

const int MOD = 666777;

int n, z;
void Add(int &a, int b) { a += b; if (a >= MOD) a -= MOD;}
int Mul(int a, int b) { return 1ll * a * b % MOD; }

struct Matrix {
    int a[41][41];
    Matrix () { memset(a, 0, sizeof(a)); }

    void Print() {
        for (int i = 0; i < z; ++i) {
            for (int j = 0; j < z; ++j) cout << a[i][j] << " \n"[j == n - 1];
        }
    }
};

Matrix operator* (const Matrix &a, const Matrix &b) {
    Matrix c;
    for (int i = 0; i < z; ++i) {
        for (int j = 0; j < z; ++j) {
            for (int k = 0; k < z; ++k) {
                Add(c.a[i][j], Mul(a.a[i][k], b.a[k][j]));
            }
        }
    }
    return c;
}

Matrix binpow(const Matrix &a, int n) {
    --n;
    Matrix ans = a, base = a;
    for (int i = 0; (1 << i) <= n; ++i) {
        if (n >> i & 1) ans = ans * base;
        base = base * base;
    }
    return ans;
}


int main()
{
    cin >> n >> z;
    ++z;
    Matrix a, b;
    for (int i = 1; i < z; ++i) {
        b.a[i][i - 1] = 1;
    }
    for (int i = 0; i < z; ++i) {
        b.a[i][z - 1] = 1;
    }
    a.a[0][z - 2] = 1;
    a.a[0][z - 1] = 1;
    Matrix ans = binpow(b, n);
    ans = a * ans;
    //ans.Print();
    cout << ans.a[0][z - 1] << '\n';
}
