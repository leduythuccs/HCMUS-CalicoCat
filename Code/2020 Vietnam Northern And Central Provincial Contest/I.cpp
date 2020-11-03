#include <bits/stdc++.h>

using namespace std;

const long double EPS = 1e-9;
const long double PI = acos(-1);

inline long double det(long double a, long double b, long double c, long double d) {
    return a*d - b*c;
}

struct Point {
    long double x, y, z;
    Point operator/(long double k) { return {x/k, y/k, z/k}; }

    Point operator-(const Point& q) const { return {x-q.x, y-q.y, z-q.z}; }
    long double operator*(const Point& q) const { return x*q.x + y*q.y + z*q.z; }
    Point operator%(Point q) const {
        return {
            det(y, z, q.y, q.z),
            -det(x, z, q.x, q.z),
            det(x, y, q.x, q.y)
        };
    }

    long double norm() const { return x*x + y*y + z*z; }
    long double len() { return sqrt(norm()); }
    Point unit() { return *this / len(); }
};
ostream& operator<<(ostream& out, Point p)
{
    return out << p.x << ' ' << p.y << ' ' << p.z << '\n';
}

Point rotate(Point p, Point h, long double alpha)
{
//    cerr << "angle = " << alpha << '\n';
    long double x = h.x, y = h.y, z = h.z;
    long double c = cos(alpha), s = sin(alpha), t = 1 - cos(alpha);
//    return {
//        p.x * (t*x*x + c + t*x*y + s*z + t*s*z - s*y),
//        p.y * (t*x*y - s*z + t*y*y + c + t*y*z + s*x),
//        p.z * (t*x*z + s*y + t*y*z - s*x + t*z*z + c)
//    };

    Point t0 = {t*x*x + c, t*x*y - s*z, t*x*z + s*y};
    Point t1 = {t*x*y + s*z, t*y*y + c, t*y*z - s*x};
    Point t2 = {t*x*z - s*y, t*y*z + s*x, t*z*z + c};
    return {t0 * p, t1 * p, t2 * p};
}

long double angle(Point a, Point o, Point b)
{
    a = a - o, b = b - o;
    return acos((a * b) / sqrt(a.norm()) / sqrt(b.norm()));
}

int main()
{
    int tests;
    cin >> tests;
    cout << setprecision(9) << fixed;
    while (tests--) {
        Point a, b, c;
        cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
        int sa, sb, sc;
        cin >> sa >> sb >> sc;
        if (sa == 0) sa = -1;
        if (sb == 0) sb = -1;
        if (sc == 0) sc = -1;
        a.z = sa * sqrt(1 - a.x*a.x - a.y*a.y);
        b.z = sb * sqrt(1 - b.x*b.x - b.y*b.y);
        c.z = sc * sqrt(1 - c.x*c.x - c.y*c.y);

        Point op = (b%c).unit();
//        cerr << "a = " << a;
//        cerr << "b = " << b;
//        cerr << "c = " << c;
//        cerr << "OP = " << op;
//        cerr << "Angle = " << angle(b, {0, 0, 0}, c) << '\n';

        Point q = rotate(a, op, angle(b, {0, 0, 0}, c));
        cout << q;
    }
    return 0;
}
