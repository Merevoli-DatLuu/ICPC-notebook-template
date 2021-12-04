void visit(int u) {
    num[u] = low[u] = ++cnt;
    st.push(u);
    int v;
    for (int i = 0; i < a[u].size(); i++) {
        v = a[u][i];
        if (num[v]) low[u] = min(low[u], num[v]);
        else {
            visit(v);
            low[u] = min(low[u], low[v]);
        }
    }
    if (num[u] == low[u]) {
        scc++;
        do {
            v = st.top();
            st.pop();
            num[v] = low[v] = oo; //TJAlG
            // num[v]=low[v]=-oo; //MESSAGE
        } while (v != u);
    }
}