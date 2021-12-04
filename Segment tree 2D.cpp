struct node {
    int id, ll, rr;
    node(int i, int l, int r) {
        id = i;
        ll = l;
        rr = r;
    }
    node left() const {
        return node(id * 2, ll, (ll + rr) / 2);
    }
    node right() const {
        return node(id * 2 + 1, (ll + rr) / 2 + 1, rr);
    }
    bool irrelevant(int l, int r) const {
        return ll > r || l > rr || l > r;
    }
};
template < class type = int >
    struct segmentTree {
        type T[4 * maxn][4 * maxn];
        int size;
        void init(int m, int n) {
            size = n * 2;
            memset(T, 0, sizeof(T));
        }
        void update(const node & dx,
            const node & dy, int u, int v, type val, bool all) {
            if (dx.irrelevant(u, u) || dy.irrelevant(v, v)) return;
            if (dx.ll == dx.rr && dy.ll == dy.rr) {
                T[dx.id][dy.id] += val;
                return;
            }
            if (all) {
                if (dx.ll != dx.rr) {
                    update(dx.left(), dy, u, v, val, true);
                    update(dx.right(), dy, u, v, val, true);
                    for (int i = 1; i < size; i++)
                        T[dx.id][i] = T[dx.left().id][i] + T[dx.right().id][i];
                } else {
                    update(dx, dy, u, v, val, false);
                }
            } else {
                if (dy.ll != dy.rr) {
                    update(dx, dy.left(), u, v, val, false);
                    update(dx, dy.right(), u, v, val, false);
                    T[dx.id][dy.id] = T[dx.id][dy.left().id] + T[dx.id][dy.right().id];
                } else {
                    T[dx.id][dy.id] += val;
                }
            }
        }
        type query(const node & dx,
            const node & dy, int u, int v, int uu, int vv) {
            if (dx.irrelevant(u, uu) || dy.irrelevant(v, vv)) return 0;
            if (u <= dx.ll && dx.rr <= uu) {
                if (v <= dy.ll && dy.rr <= vv) return T[dx.id][dy.id];
                type sum1 = query(dx, dy.left(), u, v, uu, vv);
                type sum2 = query(dx, dy.right(), u, v, uu, vv);
                return sum1 + sum2;
            } else {
                type sum1 = query(dx.left(), dy, u, v, uu, vv);
                type sum2 = query(dx.right(), dy, u, v, uu, vv);
                return sum1 + sum2;
            }
        }
    };
segmentTree < int > it;
node dx_(1, 1, maxn * 2);
node dy_(1, 1, maxn * 2);