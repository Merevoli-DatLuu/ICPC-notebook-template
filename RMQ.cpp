int n, a[maxn], log_2[maxn], rmq[maxl][maxn];
void initlog_2() {
    log_2[1] = 0;
    for (int i = 2; i <= n; i++) log_2[i] = log_2[i / 2] + 1;
}
void initRMQ() {
    for (int i = 1; i <= n; i++) rmq[0][i] = a[i];
    for (int k = 1;
        (1 << k) <= n; k++)
        for (int i = 1; i + (1 << k) - 1 <= n; i++)
            rmq[k][i] = min(rmq[k - 1][i], rmq[k - 1][i + (1 << (k - 1))]);
}
int getRMQ(int u, int v) {
    int k = log_2[v - u + 1];
    return min(rmq[k][u], rmq[k][v - (1 << k) + 1]);
}