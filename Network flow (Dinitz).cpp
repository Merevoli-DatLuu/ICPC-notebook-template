const int N = 1003,
    oo = 0x3c3c3c3c;
int n, m, S, T, d[N], c[N][N], f[N][N], Dfs[N], t = 0;
vector < int > a[N];
bool bfs(int S, int T) {
    memset(d, 0, sizeof d);
    queue < int > qu;
    qu.push(S);
    d[S] = 1;
    while (qu.size()) {
        int u = qu.front();
        qu.pop();
        if (u == T) return true;
        for (int v: a[u])
            if (!d[v] && f[u][v] < c[u][v]) {
                qu.push(v);
                d[v] = d[u] + 1;
            }
    }
    return false;
}
int visit(int u, int Min) {
    if (u == T) return Min;
    if (Dfs[u] != t) Dfs[u] = t;
    else return 0;
    for (int v: a[u])
        if (f[u][v] < c[u][v])
            if (Dfs[v] != t && d[v] == d[u] + 1)
                if (int x = visit(v, min(Min, c[u][v] - f[u][v]))) {
                    f[u][v] += x;
                    f[v][u] -= x;
                    return x;
                }
    return 0;
}