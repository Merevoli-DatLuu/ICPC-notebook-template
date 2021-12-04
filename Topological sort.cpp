int n;
vector < int > a[maxn];
bool vi[maxn];
vector < int > t;
void toposortDFS(int u) {
    vi[u] = true;
    for (int i = 0; i < a[u].size(); i++)
        if (!vi[a[u][i]]) {
            toposortDFS(a[u][i]);
        }
    t.push_back(u);
}
void toposortDEG(int u) {
    int c[maxn] = {};
    stack < int > st;
    while (st.size()) st.pop();
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < a[i].size(); j++) {
            c[a[i][j]]++;
        }
    for (int i = 1; i <= n; i++)
        if (c[i] == 0) {
            st.push(i);
        }
    while (st.size()) {
        int u = st.top();
        st.pop();
        t.push_back(u);
        for (int i = 0; i < a[u].size(); i++) {
            c[a[u][i]]--;
            if (c[a[u][i]] == 0) st.push(a[u][i]);
        }
    }
    reverse(t.begin(), t.end());
}