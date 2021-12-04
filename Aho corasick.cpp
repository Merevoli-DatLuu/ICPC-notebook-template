namespace trie {
    const int N = 2003;
    int a[N][128] Peak = 0, Prev[N];
    bool Leaf[N];
    void clear() {
        Peak = 0;
        memset(a, 0, sizeof a);
        memset(Prev, 0, sizeof Prev);
        memset(Leaf, 0, sizeof Leaf);
    }
    void insert(char s[]) {
        int u = 0;
        for (int i = 0; char k = s[i]; i++) {
            if (!a[u][k]) a[u][k] = ++Peak;
            u = a[u][k];
        }
        Leaf[u] = true;
    }
    int next(int u, char k) {
        for (int i = u; i != -1; i = Prev[i])
            if (a[i][k]) return a[i][k];
        return 0;
    }
    void bfs() {
        queue < int > qu;
        qu.push(0);
        Prev[0] = -1;
        while (qu.size()) {
            int u = qu.front();
            qu.pop();
            for (int k = 0; k < 128; k++)
                if (int v = a[u][k]) {
                    Prev[v] = next(Prev[u], k);
                    Leaf[v] |= Leaf[Prev[v]];
                    qu.push(v);
                }
        }
    }
};