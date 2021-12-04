struct Line {
    double a, b, c;
    Point A, B; // Added for polygon intersect line.
    Line(double a, double b, double c): a(a), b(b), c(c) {}
    Line(Point A, Point B): A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }
    Line(Point P, double m) {
        a = -m;
        b = 1;
        c = -((a * P.x) + (b * P.y));
    }
    double f(Point A) {
        return a * A.x + b * A.y + c;
    }
};
bool areParallel(Line l1, Line l2) {
    return cmp(l1.a * l2.b, l1.b * l2.a) == 0;
}
bool areSame(Line l1, Line l2) {
    return
    areParallel(l1, l2) && cmp(l1.c * l2.a, l2.c * l1.a) == 0 && cmp(l1.c * l2.b, l1.b * l2.c) == 0;
}
bool areIntersect(Line l1, Line l2, Point & p) {
    if (areParallel(l1, l2)) return false;
    double dx = l1.b * l2.c - l2.b * l1.c;
    double dy = l1.c * l2.a - l2.c * l1.a;
    double d = l1.a * l2.b - l2.a * l1.b;
    p = Point(dx / d, dy / d);
    return true;
}
void closestPoint(Line l, Point p, Point & ans) {
    if (fabs(l.b) < EPS) {
        ans.x = -(l.c) / l.a;
        ans.y = p.y;
        return;
    }
    if (fabs(l.a) < EPS) {
        ans.x = p.x;
        ans.y = -(l.c) / l.b;
        return;
    }
    Line perp(l.b, -l.a, -(l.b * p.x - l.a * p.y));
    areIntersect(l, perp, ans);
}
void reflectionPoint(Line l, Point p, Point & ans) {
    Point b;
    closestPoint(l, p, b);
    ans = p + (b - p) * 2;
}