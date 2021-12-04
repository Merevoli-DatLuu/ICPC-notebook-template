typedef vector < Point > Polygon;
double area2(Point a, Point b, Point c) {
    return a % b + b % c + c % a;
}
#ifdef REMOVE_REDUNDANT
bool between(const Point & a,
    const Point & b,
        const Point & c) {
    return (fabs(area2(a, b, c)) < EPS && (a.x - b.x) * (c.x - b.x) <= 0 && (a.y - b.y) * (c.y - b.y) <= 0);
}
#endif
void ConvexHull(Polygon & pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    Polygon up, dn;
    for (int i = 0; i < pts.size(); i++) {
        while (up.size() > 1 && area2(up[up.size() - 2], up.back(), pts[i]) >= 0)
            up.pop_back();
        while (dn.size() > 1 && area2(dn[dn.size() - 2], dn.back(), pts[i]) <= 0)
            dn.pop_back();
        up.push_back(pts[i]);
        dn.push_back(pts[i]);
    }
    pts = dn;
    for (int i = (int) up.size() - 2; i >= 1; i--) pts.push_back(up[i]);
    #ifdef REMOVE_REDUNDANT
    if (pts.size() <= 2) return;
    dn.clear();
    dn.push_back(pts[0]);
    dn.push_back(pts[1]);
    for (int i = 2; i < pts.size(); i++) {
        if (between(dn[dn.size() - 2], dn[dn.size() - 1], pts[i])) dn.pop_back();
        dn.push_back(pts[i]);
    }
    if (dn.size() >= 3 && between(dn.back(), dn[0], dn[1])) {
        dn[0] = dn.back();
        dn.pop_back();
    }
    pts = dn;
    #endif
}
Polygon convex_hull(Polygon P) {
    Polygon tmp = P;
    ConvexHull(tmp);
    return tmp;
}
double signed_area(Polygon p) {
    double area = 0;
    for (int i = 0; i < p.size(); i++) {
        int j = (i + 1) % p.size();
        area += p[i].x * p[j].y - p[j].x * p[i].y;
    }
    return area / 2.0;
}
double area(const Polygon & p) {
    return fabs(signed_area(p));
}
Point centroid(Polygon p) {
    Point c(0, 0);
    double scale = 6.0 * signed_area(p);
    for (int i = 0; i < p.size(); i++) {
        int j = (i + 1) % p.size();
        c = c + (p[i] + p[j]) * (p[i].x * p[j].y - p[j].x * p[i].y);
    }
    return c / scale;
}
double perimeter(Polygon P) {
    double res = 0;
    for (int i = 0; i < P.size(); ++i) {
        int j = (i + 1) % P.size();
        res += (P[i] - P[j]).len();
    }
    return res;
}
bool is_convex(const Polygon & P) {
    int sz = (int) P.size();
    if (sz <= 2) return false;
    int isLeft = ccw(P[0], P[1], P[2]);
    for (int i = 1; i < sz; i++)
        if (ccw(P[i], P[(i + 1) % sz], P[(i + 2) % sz]) * isLeft < 0) return false;
    return true;
}
bool in_polygon(const Polygon & p, Point q) {
    if ((int) p.size() == 0) return false;
    int n = (int) p.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        Point u = p[i], v = p[j];
        if (u > v) swap(u, v);
        if (ccw(u, v, q) == 0 && u <= q && q <= v) return true;
    }
    int c = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        if ((p[i].y <= q.y && q.y < p[j].y || p[j].y <= q.y && q.y < p[i].y) &&
            q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y)) c = !c;
    }
    return c;
}
#define Det(a, b, c)\
    ((double)(b.x - a.x) * (double)(c.y - a.y)\ -
        (double)(b.y - a.y) * (double)(c.x - a.x))
bool in_convex(Polygon & l, Point p) {
    int a = 1, b = l.size() - 1, c;
    if (Det(l[0], l[a], l[b]) > 0) swap(a, b);
    if (Det(l[0], l[a], p) >= 0 || Det(l[0], l[b], p) <= 0) return false;
    while (abs(a - b) > 1) {
        c = (a + b) / 2;
        if (Det(l[0], l[c], p) > 0) b = c;
        else a = c;
    }
    return Det(l[a], l[b], p) < 0;
}
Polygon polygon_cut(const Polygon & P, Line l) {
    Polygon Q;
    for (int i = 0; i < P.size(); ++i) {
        Point A = P[i], B = (i == P.size() - 1) ? P[0] : P[i + 1];
        if (ccw(l.A, l.B, A) != -1) Q.push_back(A);
        if (ccw(l.A, l.B, A) * ccw(l.A, l.B, B) < 0) {
            Point p;
            areIntersect(Line(A, B), l, p);
            Q.push_back(p);
        }
    }
    return Q;
}
bool intersect_1pt(Point a, Point b, Point c, Point d, Point & r) {
    double D = (b - a) % (d - c);
    if (cmp(D, 0) == 0) return false;
    double t = ((c - a) % (d - c)) / D;
    double s = -((a - c) % (b - a)) / D;
    r = a + (b - a) * t;
    return cmp(t, 0) >= 0 && cmp(t, 1) <= 0 && cmp(s, 0) >= 0 && cmp(s, 1) <= 0;
}
Polygon convex_intersect(Polygon P, Polygon Q) {
    const int n = P.size(),
        m = Q.size();
    int a = 0, b = 0, aa = 0, ba = 0;
    enum {
        Pin,
        Qin,
        Unknown
    } in = Unknown;
    Polygon R;
    do {
        int a1 = (a + n - 1) % n, b1 = (b + m - 1) % m;
        double C = (P[a] - P[a1]) % (Q[b] - Q[b1]);
        Point r;
        double A = (P[a1] - Q[b]) % (P[a] - Q[b]);
        double B = (Q[b1] - P[a]) % (Q[b] - P[a]);
        if (intersect_1pt(P[a1], P[a], Q[b1], Q[b], r)) {
            if ( in == Unknown) aa = ba = 0;
            R.push_back(r); in = B > 0 ? Pin : A > 0 ? Qin : in ;
        }
        if (C == 0 && B == 0 && A == 0) {
            if ( in == Pin) {
                b = (b + 1) % m;
                ++ba;
            } else {
                a = (a + 1) % m;
                ++aa;
            }
        } else if (C >= 0) {
            if (A > 0) {
                if ( in == Pin) R.push_back(P[a]);
                a = (a + 1) % n;
                ++aa;
            } else {
                if ( in == Qin) R.push_back(Q[b]);
                b = (b + 1) % m;
                ++ba;
            }
        } else {
            if (B > 0) {
                if ( in == Qin) R.push_back(Q[b]);
                b = (b + 1) % m;
                ++ba;
            } else {
                if ( in == Pin) R.push_back(P[a]);
                a = (a + 1) % n;
                ++aa;
            }
        }
    } while ((aa < n || ba < m) && aa < 2 * n && ba < 2 * m);
    if ( in == Unknown) {
        if (in_convex(Q, P[0])) return P;
        if (in_convex(P, Q[0])) return Q;
    }
    return R;
}
double convex_diameter(Polygon pt) {
    const int n = pt.size();
    int is = 0, js = 0;
    for (int i = 1; i < n; ++i) {
        if (pt[i].y > pt[is].y) is = i;
        if (pt[i].y < pt[js].y) js = i;
    }
    double maxd = (pt[is] - pt[js]).norm();
    int i, maxi, j, maxj;
    i = maxi = is;
    j = maxj = js;
    do {
        int jj = j + 1;
        if (jj == n) jj = 0;
        if ((pt[i] - pt[jj]).norm() > (pt[i] - pt[j]).norm()) j = (j + 1) % n;
        else i = (i + 1) % n;
        if ((pt[i] - pt[j]).norm() > maxd) {
            maxd = (pt[i] - pt[j]).norm();
            maxi = i;
            maxj = j;
        }
    } while (i != is || j != js);
    return maxd; /* farthest pair is (maxi, maxj). */
}
#define MAXN 100
double mindist = 1e20;
Point x, y;
bool cmpy(Point u, Point v) {
    if (u.x == v.x) return u.y < v.y;
    return u.x < v.x;
}
void upd_ans(Point _x, Point _y) {
    x = _x;
    y = _y;
}
void rec(int l, int r, Point a[]) {
    if (r - l <= 3) {
        for (int i = l; i <= r; ++i)
            for (int j = i + 1; j <= r; ++j) upd_ans(a[i], a[j]);
        sort(a + l, a + r + 1, cmpy);
        return;
    }
    int m = (l + r) >> 1;
    int midx = a[m].x;
    rec(l, m, a), rec(m + 1, r, a);
    static Point t[MAXN];
    merge(a + l, a + m + 1, a + m + 1, a + r + 1, t, cmpy);
    copy(t, t + r - l + 1, a + l);
    int tsz = 0;
    for (int i = l; i <= r; ++i)
        if (fabs(a[i].x - midx) < mindist) {
            for (int j = tsz - 1; j >= 0 && a[i].y - t[j].y < mindist; --j) upd_ans(a[i], t[j]);
            t[tsz++] = a[i];
        }
}
bool isSquare(long long x) {
    long long tmp = (long long) sqrt(x);
    return (x == tmp * tmp);
}
bool isIntegerCoordinates(int x, int y, int z) {
    long long s = (long long)(x + y + z) * (x + y - z) * (x + z - y) * (y + z - x);
    return (s % 4 == 0 && isSquare(s / 4));
}