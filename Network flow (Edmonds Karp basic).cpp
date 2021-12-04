int n, m, source, target;
vector < int > a[12309];
long c[2309][2309], f[2309][2309], d[12309];
const long oo = 1000111000111000;
void minimize(long & a, long b) {
    if (a > b) a = b;
}
bool findpath(int start, int target) {
    queue < int > qu;
    int i, u, v;
    for (i = 1; i <= n; i++) d[i] = 0;
    d[start] = oo;
    qu.push(start);
    while (qu.size()) {
        u = qu.front();
        qu.pop();
        if (u == target) return true;
        for (i = 0; v = a[u][i]; i++)
            if (d[v] == 0 && c[u][v] > f[u][v]) {
                d[v] = u;
                qu.push(v);
            }
    }
    return false;
}
void enlarge() {
    long u, v, delta = oo;
    for (v = target;
        (u = d[v]) != oo; v = u) minimize(delta, c[u][v] - f[u][v]);
    for (v = target; v != source; v = u) {
        u = d[v];
        f[u][v] += delta;
        f[v][u] -= delta;
    }
}
long answer(int u) {
    int i, v;
    long r = 0;
    for (i = 0; v = a[u][i]; i++) r += f[u][v];
    return r;
}