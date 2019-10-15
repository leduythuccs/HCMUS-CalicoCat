#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
const int N = 1 << 21;
const int K = 5050;
int fact[N], inv_fact[N];

int Mul(int a, int b) { return 1ll* a * b % MOD; }
void Add(int &a, int b) { a += b; a -= (a >= MOD ? MOD : 0); }
int sumX2[K], sumX[K], a[N], Total[K];

int binpow(int n, int k) {
    if (k == 0) return 1;
    int t = binpow(n, k >> 1);
    t = Mul(t, t);
    if (k % 2) return Mul(t, n);
    return t;
}

int C(int k, int n) {
    if (k > n) return 0;
    return Mul(fact[n], Mul(inv_fact[n - k], inv_fact[k]));
}

// typedef complex<double> ComplexType;

// const double PI = acos(-1);
// const ComplexType I(0.0, 1.0);
// const int MAX2N = 1 << 18;

// ComplexType root_unity[MAX2N + 1];

// void init_fft()
// {
//     for (int i = 0; i <= MAX2N; ++i)
//         root_unity[i] = exp(2 * PI * i / MAX2N * -I);
// }

// void fft(vector<ComplexType>& a, const vector<int>& p) {
//     int n = a.size();
//     vector<ComplexType> b(n);
//     for (int i = 0; i < n; ++i)
//         b[i] = a[p[i]];
//     copy(b.begin(), b.end(), a.begin());
//     for (int m = 1, t = MAX2N / 2; m < n; m *= 2, t /= 2)
//         for (int i = 0; i < n; i += m * 2)
//             for (int j = 0; j < m; ++j) {
//                 int u = i + j, v = i + j + m;
//                 a[v] *= root_unity[j * t];
//                 ComplexType tmp = a[u] - a[v];
//                 a[u] += a[v];
//                 a[v] = tmp;
//             }
// }

// vector<int> polymul(const vector<int>& a, const vector<int>& b) {
//     int n = max(a.size(), b.size());
//     if (__builtin_popcount(n) != 1) n = 1 << (32 - __builtin_clz(n));
//     n *= 2;
//     vector<ComplexType> pa(n), pb(n);
//     copy(a.begin(), a.end(), pa.begin());
//     copy(b.begin(), b.end(), pb.begin());

//     vector<int> p(n);
//     for (int i = 1; i < n; ++i)
//         if (i & 1) p[i] = p[i - 1] + n / 2;
//         else p[i] = p[i / 2] / 2;

//     fft(pa, p), fft(pb, p);
//     transform(pa.begin(), pa.end(), pb.begin(), pa.begin(), multiplies<ComplexType>());
//     // inverse FFT
//     for_each(pa.begin(), pa.end(), [](ComplexType& c) { c = conj(c); });
//     fft(pa, p);

//     vector<int> res(n);
//     transform(pa.begin(), pa.end(), res.begin(), [&](ComplexType c) {
//         return llround(c.real() / n) % MOD;
//     });
//     return res;
// }

struct Complex {
    double re, im;
    Complex(double r_ = 0, double i_ = 0): re(r_), im(i_) {}
    Complex operator*(const Complex& z) const { return Complex(re * z.re - im * z.im, re * z.im + im * z.re); }
    Complex operator+(const Complex& z) const { return Complex(re + z.re, im + z.im); }
    Complex operator-(const Complex& z) const { return Complex(re - z.re, im - z.im); }
    Complex normal() const { return Complex(im, -re); }
};
Complex conj(const Complex& z) { return Complex(z.re, -z.im); }

const double PI = acos(-1);
// const int N = (1 << 21);

Complex root_unity[N + 1];
void init_fft() {
    for (int i = 0; i <= N; ++i)
        root_unity[i] = Complex(cos(2 * PI * i / N), -sin(2 * PI * i / N));
}

void fft(vector<Complex>& a, const vector<int>& p) {
    int n = a.size();
    for (int i = 0; i < n; ++i)
        if (i < p[i]) swap(a[i], a[p[i]]);
    for (int m = 1, t = N / 2; m < n; m *= 2, t /= 2)
        for (int i = 0; i < n; i += m * 2)
            for (int j = 0; j < m; ++j) {
                int u = i + j, v = i + j + m;
                a[v] = a[v] * root_unity[j * t];
                Complex tmp = a[u] - a[v];
                a[u] = a[u] + a[v];
                a[v] = tmp;
            }
}

vector<int> polymul(const vector<int>& a, const vector<int>& b) {
    int n = max(a.size(), b.size());
    if (__builtin_popcount(n) != 1) n = 1 << (32 - __builtin_clz(n));
    n *= 2;
    vector<Complex> pa(n);
    for (size_t i = 0; i < a.size(); ++i) pa[i] = Complex(a[i], b[i]);

    vector<int> p(n);
    for (int i = 0; i < n; ++i)
        p[i] = p[i >> 1] >> 1 | ((i & 1) << (30 - __builtin_clz(n)));

    fft(pa, p);
    vector<Complex> pb(n);
    pb[0] = pa[0].re * pa[0].im;
    for (int i = 1; i < n; ++i) {
        Complex ai = pa[i] + conj(pa[n - i]);
        Complex bi = pa[i] - conj(pa[n - i]);
        pb[i] = conj(ai * bi.normal() * (1./4));
    }
    fft(pb, p);

    vector<int> res(n);
    transform(pb.begin(), pb.end(), res.begin(), [&](Complex c) { return llround(c.re / n) % MOD; });
    return res;
}

vector<int> bigmul(const vector<int>& a, const vector<int>& b)
{
    const int BASE = sqrt(1e9);
    vector<int> aBig, aSmall, bBig, bSmall;
    for (int x : a) {
        aBig.push_back(x / BASE);
        aSmall.push_back(x % BASE);
    }
    for (int x : b) {
        bBig.push_back(x / BASE);
        bSmall.push_back(x % BASE);
    }
    vector<int> res = polymul(aSmall, bSmall);
    vector<int> tmp = polymul(aBig, bSmall);
    for (size_t i = 0; i < tmp.size(); ++i)
        Add(res[i], Mul(tmp[i], BASE));
    tmp = polymul(aSmall, bBig);
    for (size_t i = 0; i < tmp.size(); ++i)
        Add(res[i], Mul(tmp[i], BASE));
    tmp = polymul(aBig, bBig);
    for (size_t i = 0; i < tmp.size(); ++i)
        Add(res[i], Mul(tmp[i], Mul(BASE, BASE)));
    return res;
}

int f[K], g[K];

int main()
{
    // double stime = clock();
    init_fft();
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) fact[i] = Mul(fact[i - 1], i);
    inv_fact[n] = binpow(fact[n], MOD - 2);
    for (int i = n; i > 0; --i)
        inv_fact[i - 1] = Mul(inv_fact[i], i);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    int ans = 0;
    int d = 0;

    vector<int> polyA(n + 1), polyC(n + 1), polyB(n + 1);
    for (int i = 0; i < n; ++i) polyA[i] = a[i + 1];
    for (int i = 0; i < n; ++i) polyC[i] = Mul(a[i + 1], a[i + 1]);
    for (int i = 1; i <= n; ++i) {
        polyB[i] = C(k - 2, i - 1);
    }
    vector<int> f = bigmul(polyC, polyB);
    vector<int> g = bigmul(polyA, polyB);

    // for (int x : f) cerr << x << ' ';
    // cerr << '\n';
    // for (int x : g) cerr << x << ' ';
    // cerr << '\n';

    int res = 0;
    for (int i = k; i <= n; ++i) {
        Add(res, f[i - 1]);
        Add(res, Mul(MOD - 2, Mul(g[i - 1], a[i])));
        Add(res, Mul(Mul(a[i], a[i]), C(k - 1, i - 1)));
        //cerr << i << ' ' << res << '\n';
    }

    cout << Mul(Mul(5, res), binpow(C(k, n), MOD - 2)) << '\n';
    // double etime = clock();
    // cerr << "Time executed: " << (etime - stime) / CLOCKS_PER_SEC << "ms.\n";
        
}
