void solve() {
    for (int i = 1; i <= n; i++) {
        f[i] = lower_bound(b + 1, b + ans + 1, a[i]) - b;
        ans = max(ans, f[i]);
        b[f[i]] = a[i];
    }
    int exp = ans;
    for (int i = n; i >= 1; i--)
        if (f[i] == exp) {
            t.push_back(a[i]);
            exp--;
        }
    reverse(t.begin(), t.end());
}