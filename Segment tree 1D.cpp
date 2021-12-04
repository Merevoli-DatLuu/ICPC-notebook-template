template < class type = int >
    struct segmentTree {
        struct nodetree {
            type tmax, tmin, lazy;
            int imax, imin;
            bool isErase;
            nodetree() {
                tmax = -oo;
                tmin = oo;
                imax = -1;
                imin = -1;
                lazy = 0;
                isErase = false;
            }
        };
        nodetree a[4 * maxn];
        int imax, imin;
        type tmax, tmin;
        void merge(int node) {
            if (a[node * 2].tmax >= a[node * 2 + 1].tmax) {
                a[node].tmax = a[node * 2].tmax;
                a[node].imax = a[node * 2].imax;
            } else {
                a[node].tmax = a[node * 2 + 1].tmax;
                a[node].imax = a[node * 2 + 1].imax;
            }
            if (a[node * 2].tmin <= a[node * 2 + 1].tmin) {
                a[node].tmin = a[node * 2].tmin;
                a[node].imin = a[node * 2].imin;
            } else {
                a[node].tmin = a[node * 2 + 1].tmin;
                a[node].imin = a[node * 2 + 1].imin;
            }
        }
        void build(int node, int ll, int rr, int u, int v) {
            if (v < ll || rr < u || ll > rr) return;
            if (u <= ll && ll == rr && rr <= v) {
                a[node].tmax = arr[ll];
                a[node].tmin = arr[ll];
                a[node].imax = ll;
                a[node].imin = ll;
            } else {
                build(node * 2, ll, (ll + rr) / 2, u, v);
                build(node * 2 + 1, (ll + rr) / 2 + 1, rr, u, v);
                merge(node);
            }
        }
        void diffuse(int node, int ll, int rr) {
            if (a[node].lazy == 0) return;
            if (a[node].lazy == -1) {
                a[node].tmax = -oo;
                a[node].tmin = oo;
                if (ll != rr) {
                    a[node * 2].lazy = -1;
                    a[node * 2 + 1].lazy = -1;
                }
            } else {
                a[node].tmax += a[node].lazy;
                a[node].tmin += a[node].lazy;
                if (ll != rr) {
                    a[node * 2].lazy += a[node].lazy;
                    a[node * 2 + 1].lazy += a[node].lazy;
                }
                a[node].lazy = 0;
            }
        }
        void update(int node, int ll, int rr, int u, int v, type val) {
            diffuse(node, ll, rr);
            if (v < ll || rr < u || ll > rr) return;
            if (u <= ll && ll <= rr && rr <= v) {
                if (val == 0) a[node].lazy = -1;
                else a[node].lazy += val;
                diffuse(node, ll, rr);
            } else {
                update(node * 2, ll, (ll + rr) / 2, u, v, val);
                update(node * 2 + 1, (ll + rr) / 2 + 1, rr, u, v, val);
                merge(node);
            }
        }
        void init() {
            tmax = -oo;
            tmin = oo;
            imax = -1;
            imin = -1;
        }
        void query(int node, int ll, int rr, int u, int v) {
            diffuse(node, ll, rr);
            if (v < ll || rr < u || ll > rr) return;
            if (u <= ll && ll <= rr && rr <= v) {
                if (tmax < a[node].tmax) {
                    tmax = a[node].tmax;
                    imax = a[node].imax;
                }
                if (tmin > a[node].tmin) {
                    tmin = a[node].tmin;
                    imin = a[node].imin;
                }
            } else {
                query(node * 2, ll, (ll + rr) / 2, u, v);
                query(node * 2 + 1, (ll + rr) / 2 + 1, rr, u, v);
            }
        }
    };