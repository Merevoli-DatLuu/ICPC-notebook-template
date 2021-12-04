class MaxClique {
    public:
        int n, el[maxn][log2maxn], s[maxn][log2maxn], dp[maxn], ans;
    vector < int > sol;
    void init(int v) {
        n = v;
        ans = 0;
        memset(el, 0, sizeof(el));
        memset(dp, 0, sizeof(dp));
    }
    void addEdge(int u, int v) {
        if (u > v) swap(u, v);
        if (u == v) return;
        el[u][v / 32] |= (1 << (v % 32));
    }
    bool dfs(int v, int k) {
        int c = 0, d = 0, t = (n + 31) / 32;
        for (int i = 0; i < t; i++) {
            s[k][i] = el[v][i];
            if (k != 1) s[k][i] &= s[k - 1][i];
            c += __builtin_popcount(s[k][i]);
        }
        if (c == 0) {
            if (k > ans) {
                ans = k;
                sol.clear();
                sol.push_back(v);
                return 1;
            }
            return 0;
        }
        for (int i = 0; i < t; i++) {
            for (int a = s[k][i]; a; d++) {
                if (k + (c - d) <= ans) return 0;
                int lb = a & (-a), lg = 0;
                a ^= lb;
                while (lb != 1) {
                    lb = (unsigned int)(lb) >> 1;
                    lg++;
                }
                int u = i * 32 + lg;
                if (k + dp[u] <= ans) return 0;
                if (dfs(u, k + 1)) {
                    sol.push_back(v);
                    return 1;
                }
            }
        }
        return 0;
    }
    int solve() {
        for (int i = n - 1; i >= 0; i--) {
            dfs(i, 1);
            dp[i] = ans;
        }
        return ans;
    }
}
mc;