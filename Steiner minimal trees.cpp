const int maxn = 30;
const int oo = 1000111000;
struct SteinerTree {
    int n, a[maxn][maxn];
    vector < int > s;
    vector < vector < int > > dp;
    void init(int _n) {
        n = _n;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) a[i][j] = oo;
        for (int i = 0; i < n; i++) a[i][i] = 0;
        s.clear();
    }
    void addEdge(int u, int v, int w) {
        a[u][v] = min(a[u][v], w);
        a[v][u] = min(a[v][u], w);
    }
    void addTerminal(int t) {
        s.push_back(t);
    }
    int minLengthSteinerTree() {
        int m = s.size();
        if (m <= 1) return 0;
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
        dp.resize(1 << m, vector < int > (n, 0));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                dp[1 << i][j] = a[s[i]][j];
        for (int i = 1; i < (1 << m); i++)
            if (((i - 1) & i) != 0) {
                for (int j = 0; j < n; j++) {
                    dp[i][j] = oo;
                    for (int k = (i - 1) & i; k > 0; k = (k - 1) & i)
                        dp[i][j] = min(dp[i][j], dp[k][j] + dp[i ^ k][j]);
                }
                for (int j = 0; j < n; j++)
                    for (int k = 0; k < n; k++)
                        dp[i][j] = min(dp[i][j], dp[i][k] + a[k][j]);
            }
        return dp[(1 << m) - 1][s[0]];
    }
}
steiner;