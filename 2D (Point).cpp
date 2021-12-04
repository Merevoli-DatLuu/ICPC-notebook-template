#define EPS 1e-6
const double PI = acos(-1.0);
double DEG_to_RAD(double d) {
    return d * PI / 180.0;
}
double RAD_to_DEG(double r) {
    return r * 180.0 / PI;
}
inline int cmp(double a, double b) {
    return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}
struct Point {
    double x, y;
    Point() {
        x = y = 0.0;
    }
    Point(double x, double y): x(x), y(y) {}
    Point operator + (const Point & a) const {
        return Point(x + a.x, y + a.y);
    }
    Point operator - (const Point & a) const {
        return Point(x - a.x, y - a.y);
    }
    Point operator * (double k) const {
        return Point(x * k, y * k);
    }
    Point operator / (double k) const {
        return Point(x / k, y / k);
    }
    double operator * (const Point & a) const {
        return x * a.x + y * a.y;
    } // dot product
    double operator % (const Point & a) const {
        return x * a.y - y * a.x;
    } // cross product
    int cmp(Point q) const {
        if (int t = ::cmp(x, q.x)) return t;
        return ::cmp(y, q.y);
    }
    #define Comp(x) bool operator x(Point q) const {
        return cmp(q) x 0;
    }
    Comp( > ) Comp( < ) Comp( == ) Comp( >= ) Comp( <= ) Comp( != )
    #undef Comp
    Point conj() {
        return Point(x, -y);
    }
    double norm() {
        return x * x + y * y;
    }
    double len() {
        return sqrt(norm());
    }
    Point rotate(double alpha) {
        double cosa = cos(alpha), sina = sin(alpha);
        return Point(x * cosa - y * sina, x * sina + y * cosa);
    }
};
int ccw(Point a, Point b, Point c) {
    return cmp((b - a) % (c - a), 0);
}
int RE_TRAI = ccw(Point(0, 0), Point(0, 1), Point(-1, 1));
int RE_PHAI = ccw(Point(0, 0), Point(0, 1), Point(1, 1));
istream & operator >> (istream & cin, Point & p) {
    cin >> p.x >> p.y;
    return cin;
}
ostream & operator << (ostream & cout, Point & p) {
    cout << p.x << ' ' << p.y;
    return cout;
}
double angle(Point a, Point o, Point b) {
    a = a - o;
    b = b - o;
    return acos((a * b) / sqrt(a.norm()) / sqrt(b.norm()));
}
double directed_angle(Point a, Point o, Point b) {
    double t = -atan2(a.y - o.y, a.x - o.x) + atan2(b.y - o.y, b.x - o.x);
    while (t < 0) t += 2 * PI;
    return t;
}
double distToLine(Point p, Point a, Point b, Point & c) {
    Point ap = p - a, ab = b - a;
    double u = (ap * ab) / ab.norm();
    c = a + (ab * u);
    return (p - c).len();
}
double distToLineSegment(Point p, Point a, Point b, Point & c) {
    Point ap = p - a, ab = b - a;
    double u = (ap * ab) / ab.norm();
    if (u < 0.0) {
        c = Point(a.x, a.y);
        return (p - a).len();
    }
    if (u > 1.0) {
        c = Point(b.x, b.y);
        return (p - b).len();
    }
    return distToLine(p, a, b, c);
}