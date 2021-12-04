int n, l, x, y;
long long a[maxn];
void LBI() {
    long long m[maxn] = {}, c[maxn] = {};
    x = 0;
    y = 0;
    for (int i = 1; i <= n; i++) {
        c[i] = c[i - 1] + a[i];
        if (c[i - 1] < c[m[i - 1]]) m[i] = i - 1;
        else m[i] = m[i - 1];
        int k = i - y + x - 1;
        while (k > 0) {
            if (c[i] - c[m[k]] >= l) k = m[k];
            else break;
            x = k + 1;
            y = i;
        }
    }
}