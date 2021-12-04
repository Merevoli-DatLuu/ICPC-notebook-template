const int maxn = 1010,
    maxm = 50010;
struct match_0 {
    int n, m, start, finish, newroot, qsize, adj[maxm], next[maxm], last[maxn],
        mat[maxn], que[maxn], dad[maxn], root[maxn];
    bool inque[maxn], inpath[maxn], inblossom[maxn];
    void init(int _n) {
        n = _n;
        m = 0;
        for (int x = 1; x <= n; x++) {
            last[x] = -1;
            mat[x] = 0;
        }
    }
    void add(int u, int v) {
        adj[m] = v;
        next[m] = last[u];
        last[u] = m++;
    }
    int lca(int u, int v) {
        for (int x = 1; x <= n; x++) inpath[x] = 0;
        while (true) {
            u = root[u];
            inpath[u] = 1;
            if (u == start) break;
            u = dad[mat[u]];
        }
        while (true) {
            v = root[v];
            if (inpath[v]) break;
            v = dad[mat[v]];
        }
        return v;
    }
    void trace(int u) {
        while (root[u] != newroot) {
            int v = mat[u];
            inblossom[root[u]] = 1;
            inblossom[root[v]] = 1;
            u = dad[v];
            if (root[u] != newroot) dad[u] = v;
        }
    }
    void blossom(int u, int v) {
        for (int x = 1; x <= n; x++) inblossom[x] = 0;
        newroot = lca(u, v);
        trace(u);
        trace(v);
        if (root[u] != newroot) dad[u] = v;
        if (root[v] != newroot) dad[v] = u;
        for (int x = 1; x <= n; x++) {
            if (inblossom[root[x]]) {
                root[x] = newroot;
                if (!inque[x]) {
                    inque[x] = 1;
                    que[qsize++] = x;
                }
            }
        }
    }
    bool bfs() {
        for (int x = 1; x <= n; x++) {
            inque[x] = 0;
            dad[x] = 0;
            root[x] = x;
        }
        qsize = 0;
        que[qsize++] = start;
        inque[start] = 1;
        finish = 0;
        for (int i = 0, u; i < qsize; i++) {
            u = que[i];
            for (int e = last[u], v; e != -1; e = next[e]) {
                v = adj[e];
                if (root[v] != root[u] && v != mat[u]) {
                    if (v == start || (mat[v] > 0 && dad[mat[v]] > 0)) blossom(u, v);
                    else if (dad[v] == 0) {
                        dad[v] = u;
                        if (mat[v] > 0) que[qsize++] = mat[v];
                        else {
                            finish = v;
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }
    void enlarge() {
        int u = finish, v, x;
        while (u > 0) {
            v = dad[u];
            x = mat[v];
            mat[v] = u;
            mat[u] = v;
            u = x;
        }
    }
    int maxMatching() {
        for (int x = 1; x <= n; x++)
            if (mat[x] == 0) {
                start = x;
                if (bfs()) enlarge();
            }
        int total = 0;
        for (int x = 1; x <= n; x++)
            if (mat[x] > x) total++;
        return total;
    }
}
match0;
void solve_match0() {
    int n, m, u, v, k;
    cin >> n >> m;
    match0.init(n + m);
    while (cin >> u >> v) {
        v += n;
        match0.add(u, v);
        match0.add(v, u);
    }
    cout << match0.maxMatching() << "\n";
    for (int x = 1, y; x <= n; x++) {
        y = match0.mat[x];
        if (y != 0) cout << x << " " << y - n << "\n";
    }
}