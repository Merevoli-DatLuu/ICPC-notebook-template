struct CRT {
    vector < LL > a, b, m;
    LL x, M;
    void init() {
        a.clear();
        b.clear();
        m.clear();
    }
    void add(LL b_, LL m_) {
        a.push_back(1 LL);
        b.push_back(b_);
        m.push_back(m_);
    }
    bool linearCongruences() {
        LL n = a.size();
        x = 0;;
        M = 1;
        for (int i = 0; i < n; i++) {
            LL a_ = a[i] * M, b_ = b[i] - a[i] * x, m_ = m[i];
            LL y, t, g = extgcd(a_, m_, y, t);
            if (b_ % g) return false;
            b_ /= g;
            m_ /= g;
            x += M * (y * b_ % m_);
            M *= m_;
        }
        x = (x + M) % M;
        return true;
    }
}
crt;