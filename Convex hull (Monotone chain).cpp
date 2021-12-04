struct Point {
    int X, Y
    bool operator < (const Point & v) {
        return X == v.X ? Y < v.Y : X < v.X;
    }
    int cross(const Point & p,
        const Point & q) const {
        return (p.X - X) * (q.Y - Y) - (p.Y - Y) * (q.X - X);
    }
};
int n;
Point a[maxn], p[maxn];
void monotonechain() {
    sort(a + 1, a + n + 1);
    int k = 1;
    for (int i = 1; i <= n; i++) {
        while (k >= 3 && p[k - 2].cross(p[k - 1], a[i]) <= 0) k--;
        p[k++] = a[i];
    }
    for (int i = n - 1, t = k + 1; i > 0; i--) {
        while (k >= t && p[k - 2].cross(p[k - 1], a[i]) <= 0) k--;
        p[k++] = a[i];
    }
    for (int i = 1; i < k; i++) a[i] = p[i];
    n = k - 2;
}