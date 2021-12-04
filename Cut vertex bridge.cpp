void visit(int u, int p) {
    int num_child = 0, v;
    num[u] = low[u] = ++cnt;
    for (int i = 0; i < a[u].size(); i++) {
        v = a[u][i];
        if (v != p) {
            if (num[v]) low[u] = min(low[u], num[v]);
            else {
                visit(v, u);
                num_child++;
                low[u] = min(low[u], low[v]);
                if (low[v] >= num[v]) {
                    bridge.push_back(II(u, v));
                }
                if (u == p) {
                    if (num_child >= 2) cutnode[u] = 1;
                } else {
                    if (low[v] >= num[u]) cutnode[u] = 1;
                }
            }
        }
    }
}