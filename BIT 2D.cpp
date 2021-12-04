template < class type = int >
    struct fenwickTree {
        int m, n;
        type T[maxn][maxn] = {};
        fenwickTree(int mm, int nn) {
            m = mm;
            n = nn;
        }
        void init(int mm, int nn) {
            m = mm;
            n = nn;
            memset(T, 0, sizeof(T));
        }
        void update(int p, int q, type val) {
            for (int i = p; i <= m; i += i & -i)
                for (int j = q; j <= n; j += j & -j) T[i][j] += val;
        }
        type query(int p, int q) {
            type r = 0;
            for (int i = p; i >= 1; i -= i & -i)
                for (int j = q; j >= 1; j -= j & -j) r += T[i][j];
            return r;
        }
        type query(int p, int q, int pp, int qq) {
            return query(pp, qq) - query(pp, q - 1) - query(p - 1, qq) + query(p - 1, q - 1);
        }
    };