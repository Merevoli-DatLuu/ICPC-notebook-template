const int SQRTN = 1 << 16; // upperbound of sqrt(H) + 10
vector < bool > segmentSieve(LL L, LL H) {
    static LL p[SQRTN];
    static int lookup = 0;
    if (!lookup) {
        for (LL i = 2; i < SQRTN; ++i) p[i] = i;
        for (LL i = 2; i * i < SQRTN; ++i)
            if (p[i])
                for (LL j = i * i; j < SQRTN; j += i) p[j] = 0;
        remove(p, p + SQRTN, 0);
        lookup = 1;
    }
    vector < bool > table(H - L);
    for (LL i = L; i < H; ++i) table[i - L] = 1;
    for (LL i = 0, j; p[i] * p[i] < H; ++i) { // O( \sqrt(H) )
        if (p[i] >= L) j = p[i] * p[i];
        else if (L % p[i] == 0) j = L;
        else j = L - (L % p[i]) + p[i];
        for (; j < H; j += p[i]) table[j - L] = 0;
    }
    return table;
}