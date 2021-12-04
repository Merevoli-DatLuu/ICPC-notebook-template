LL f(LL x, LL m, LL k) {
    return (mul_mod(x, x, m) + k % m) % m;
}
LL pollard_rho(LL n, LL k) {
    LL a = 2, b = 2;
    do {
        a = f(a, n, k);
        b = f(b, n, k);
        b = f(b, n, k);
        LL p = gcd(abs(b - a), n);
        if (p > 1) return p;
    } while (a != b);
    return n;
}
LL get_factor(LL n) {
    if (n == 1) return n;
    if (isPrime(n)) return n;
    if (n == 4) return 2;
    LL p = n, q;
    for (LL k = 1; p == n; k++) {
        p = pollard_rho(n, k);
        q = n / p;
    }
    return p;
}