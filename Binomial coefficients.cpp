const int maxn = 60;
ULL BC[maxn][maxn];
void binomialCoeff() {
    BC[0][0] = 1;
    for (int i = 1; i < maxn; i++)
        for (int j = 0; j <= i; j++)
            if (j == 0) BC[i][j] = 1;
            else BC[i][j] = BC[i - 1][j - 1] + BC[i - 1][j];
}
ULL binomialCoeff(int n, int k) {
    ULL res = 1;
    if (k >= n - k) k = n - k;
    for (int i = 0; i < k; i++) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}