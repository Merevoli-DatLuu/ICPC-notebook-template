LL josephus(LL n, LL k) {
    LL p = n * k;
    LL nn = n + 1, kk = k - 1;
    while (p > n) {
        p += (p - nn) / kk - n;
    }
    return p;
}