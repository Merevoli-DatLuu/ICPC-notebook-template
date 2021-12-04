LL extgcd(LL a, LL b, LL & x, LL & y) {
    LL g = a;
    x = 1;
    y = 0;
    if (b != 0) {
        g = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }
    return g;
}
LL mod_inv(LL a, LL m) {
    LL x, y;
    extgcd(a, m, x, y);
    return (m + x % m) % m;
}