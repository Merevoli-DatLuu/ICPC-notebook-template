template < class type = int >
    struct fenwickTree {
        int n, logn;
        type T[maxn] = {};
        fenwickTree(int nn) {
            n = 1;
            logn = 0;
            while (n < nn) n *= 2, logn++;
        }
        void update(int id, type val) {
            for (int i = id; i <= n; i += i & -i) T[i] += val;
        }
        type query(int id) {
            type r = 0;
            for (int i = id; i >= 1; i -= i & -i) r += T[i];
            return r;
        }
        type query(int ll, int rr) {
            return query(rr) - query(ll - 1);
        }
        int lower_bound(int r, int l, type val) {
            for (int i = l - 1; i >= 0; i--)
                if (T[r - (1 << i)] >= val) return lower_bound(r - (1 << i), i, val);
                else val -= T[i];
            return r;
        }
        int lower_bound(type val) {
            if (val > T[n]) return 0;
            else return lower_bound(n, logn, val);
        }
    };