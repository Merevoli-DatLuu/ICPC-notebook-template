int n, m, cnt;
vector < int > * a;
int * color, * num, * low;
stack < int > st;
bool invalid = 0;
#define SetLength(a, n, t) a = ((t * ) calloc(n, sizeof(t))) + (n) / 2
void init(int m, int n) {
    SetLength(a, n * 2 + 10, vector < int > );
    SetLength(color, n * 2 + 10, int);
    SetLength(num, n * 2 + 10, int);
    SetLength(low, n * 2 + 10, int);
}
void setColor(int u, int x) {
    if (color[u] == (x ^ 3)) invalid = 1;
    else color[u] = x;
    if (color[-u] == x) invalid = 1;
    else color[-u] = (x ^ 3);
}
void tarzan(int u) {
    num[u] = low[u] = ++cnt;
    st.push(u);
    for (int i = 0, v; i < a[u].size(); i++) {
        v = a[u][i];
        if (num[v]) low[u] = min(low[u], num[v]);
        else tarzan(v), low[u] = min(low[u], low[v]);
        if (color[v] == 1) setColor(u, 1); // set false
    }
    if (low[u] == num[u]) {
        int v = 0;
        if (color[u] == 0) setColor(u, 2); // set true
        do {
            v = st.top();
            st.pop();
            setColor(v, color[u]);
            num[v] = low[v] = oo;
        } while (u != v);
    }
}
void input() {
    cin >> m >> n;
    init(m, n);
    int p, q;
    for (int i = 1; i <= m; i++) {
        cin >> p >> q;
        a[-p].push_back(q);
        a[-q].push_back(p);
    }
}
void solve() {
    for (int i = 1; i <= n; i++)
        if (!num[i]) tarzan(i);
    for (int i = 1; i <= n; i++)
        if (!num[-i]) tarzan(-i);
}
void output() {
    if (invalid) cout << "NO\n";
    else {
        cout << "YES\n";
        int ans = 0;
        for (int i = 1; i <= n; i++)
            if (color[i] == 2) ans++;
        cout << ans << "\n";
        for (int i = 1; i <= n; i++)
            if (color[i] == 2) cout << i << " ";
        cout << "\n";
    }
}