void check_bipartite(int u) {
    visit[u] = 1;
    for (int i = 0, v; i < a[u].size(); i++) {
        v = a[u][i];
        if (!visit[v]) {
            color[v] = 3 - color[u];
            check_bipartite(v);
        } else {
            if (color[u] == color[v]) invalid = 1;
        }
    }
}