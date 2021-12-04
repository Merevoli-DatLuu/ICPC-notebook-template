VLL primeFactors(LL x) {
    VLL f;
    LL i = 0, n = primes[i];
    while (n * n <= x) {
        while (x % n == 0) {
            x /= n;
            f.push_back(n);
        }
        n = primes[++i];
    }
    if (x != 1) f.push_back(x);
    return f;
}
LL sumDiv(LL x) {
    LL i = 0, n = primes[i], ans = 1;
    while (n * n <= x) {
        int c = 0;
        while (x % n == 0) {
            c++;
            x /= n;
        }
        ans *= (pow(n, c + 1) - 1) / (n - 1);
        n = primes[++i];
    }
    if (x != 1) ans *= (pow(x, 2) - 1) / (x - 1);
    return ans;
}
LL EulerPhi(LL x) {
    if (n == 0) return 0;
    LL i = 0, n = primes[i], phi = x;
    while (n * n <= x) {
        if (x % n == 0) phi -= phi / n;
        while (x % n == 0) x /= n;
        n = primes[++i];
    }
    if (x != 1) phi -= phi / x;
    return phi;
}
LL f[maxn], p[maxn];
void init_EulerPhi(LL n) {
    bool stop = false;
    if (!stop) {
        for (int i = 1; i < n; i++) p[i] = 1, f[i] = i;
        for (int i = 2; i < n; i++) {
            if (p[i]) {
                f[i] -= f[i] / i;
                for (int j = i + i; j < n; j += i) p[j] = 0, f[j] -= f[j] / i;
            }
        }
        stop = true;
    }
}