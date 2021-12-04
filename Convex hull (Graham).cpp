Point O;
int n;
Point a[maxn];
void operator -= (Point & a, Point b) {
    a.X -= b.X;
    a.Y -= b.Y;
}
bool ccw(Point o, Point a, Point b) {
    a -= o;
    b -= o;
    return a.X * b.Y > a.Y * b.X;
}
bool cmp(Point a, Point b) {
    return ccw(O, a, b);
}
void graham() {
    sort(a + 1, a + n + 1);
    O = a[1];
    sort(a + 2, a + n + 1, cmp);
    a[0] = a[n];
    a[n + 1] = a[1];
    int j = 1;
    for (int i = 1; i <= n + 1; i++) {
        while (j > 2 && !ccw(a[j - 2], a[j - 1], a[i])) j--;
        a[j++] = a[i];
    }
    n = j - 2;
}