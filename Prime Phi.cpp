LL p[maxn][maxp];
LL phi[maxn];
LL phi_[maxn];
void phi_function() {
    for (int i = 1; i < maxn; i++) phi_[i] = i;
    for (int i = 2; i < maxn; i++)
        if (phi_[i] == i)
            for (int j = i; j < maxn; j += i) phi_[j] = (phi_[j] / i) * (i - 1);
}
LL power(int a, int k) {
    if (k == 0) return 1;
    if (p[a][k] > 0) return p[a][k];
    LL t = power(a, k / 2);
    t *= t;
    if (k % 2 == 1) t *= a;
    return p[a][k] = t;
}
LL phi_function(int p, int k) {
    if (k == 0) return 1;
    return (p - 1) * power(p, k - 1);
}
LL phi_function(int m) {
    if (phi[m] > 0) return phi[m];
    LL r = 1, t = m, k;
    for (int i = 2; i * i <= t; i++) {
        k = 0;
        while (t % i == 0) k++, t /= i;
        r *= phi_function(i, k);
    }
    if (t > 1) r *= phi_function(t, 1);
    return phi[m] = r;
}