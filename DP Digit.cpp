const int maxd = 25,
    maxt = 2;
LL dp[maxd][maxt];
unordered_map < LL, LL > mm;
vector < int > d;
struct DP_digit {
    void getDigit(LL n) {
        d.clear();
        while (n) {
            d.push_back(n % 10);
            n /= 10;
        }
    }
    LL calc(int pos, bool tight, LL sum) {
        if (pos == -1) return sum;
        if (dp[pos][tight] != -1) return dp[pos][tight];
        LL res = 0;
        int k = (tight) ? d[pos] : 9;
        bool ntight;
        for (int i = 0; i <= k; i++) {
            ntight = (d[pos] == i) ? tight : 0;
            res += calc(pos - 1, ntight, sum + i);
        }
        return res;
    }
    LL calc(LL u) {
        if (mm.count(u)) return mm[u];
        memset(dp, -1, sizeof(dp));
        getDigit(u);
        return mm[u] = calc(d.size() - 1, 1, 0);
    }
    LL calc(LL u, LL v) {
        return calc(v) - calc(u - 1);
    }
};