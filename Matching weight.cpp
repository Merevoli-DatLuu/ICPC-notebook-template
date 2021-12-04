struct match_2 {
    int n;
    VI d, arg, trace, fx, fy, mx, my;
    VVI cost, adj;
    queue < int > qu;
    void init(int _nx, int _ny) {
        n = max(_nx, _ny);
        cost = VVI(n, VI(n, oo));
        adj = VVI(n);
        d = VI(n);
        arg = VI(n);
        trace = VI(n);
        fx = VI(n);
        fy = VI(n);
        mx = VI(n, -1);
        my = VI(n, -1);
    }
    void add(int u, int v, int w) {
        if (cost[u][v] == oo) adj[u].push_back(v);
        if (cost[u][v] > w) cost[u][v] = w;
    }
    int getCost(int x, int y) {
        return cost[x][y] - fx[x] - fy[y];
    }
    void initBFS(int start) {
        for (int i = 0; i < n; i++) trace[i] = -1;
        while (qu.size()) qu.pop();
        qu.push(start);
        for (int i = 0; i < n; i++) {
            d[i] = getCost(start, i);
            arg[i] = start;
        }
    }
    int findPath() {
        int x, y, w;
        while (qu.size()) {
            x = qu.front();
            qu.pop();
            for (int i = 0; i < adj[x].size(); i++) {
                y = adj[x][i];
                if (trace[y] == -1) {
                    w = getCost(x, y);
                    if (w == 0) {
                        trace[y] = x;
                        if (my[y] == -1) return y;
                        qu.push(my[y]);
                    }
                    if (d[y] > w) {
                        d[y] = w;
                        arg[y] = x;
                    }
                }
            }
        }
        return -1;
    }
    int update(int start) {
        int delta = oo;
        for (int y = 0; y < n; y++)
            if (trace[y] == -1) delta = min(delta, d[y]);
        fx[start] += delta;
        for (int y = 0, x; y < n; y++)
            if (trace[y] != -1) {
                x = my[y];
                fx[x] += delta;
                fy[y] -= delta;
            }
        else d[y] -= delta;
        for (int y = 0; y < n; y++)
            if (trace[y] == -1 && d[y] == 0) {
                trace[y] = arg[y];
                if (my[y] == -1) return y;
                qu.push(my[y]);
            }
        return -1;
    }
    void enlarge(int finish) {
        for (int y = finish, x, yy; y != -1;) {
            x = trace[y];
            yy = mx[x];
            mx[x] = y;
            my[y] = x;
            y = yy;
        }
    }
    int maxMatching() {
        for (int x = 0; x < n; x++) {
            initBFS(x);
            int finish = -1;
            while (finish == -1) {
                finish = findPath();
                if (finish != -1) break;
                finish = update(x);
            }
            enlarge(finish);
        }
        int total = 0;
        for (int x = 0; x < n; x++)
            if (cost[x][mx[x]] != oo) total += cost[x][mx[x]];
        return total;
    }
}
match2;
void solve_match2() {
    int n, u, v, w;
    cin >> n;
    match2.init(n + 1, n + 1);
    while (cin >> u >> v >> w) {
        match2.add(u, v, w);
    }
    cout << match2.maxMatching() << "\n";
    for (int x = 1, y; x <= n; x++) {
        y = match2.mx[x];
        if (y != -1) cout << x << " " << y << "\n";
    }
}