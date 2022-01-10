/*
Graph traversal (dfs)
First line input n,m
m lines with bidirectional edges between n,m (nodes numbered starting at 1)
*/

int n,m; cin >> n >> m;
VVI adj(n);
REP(i, m) {
    int a,b; cin >> a >> b;
    --a; -- b;
    adj[a].PB(b);
    adj[b].PB(a);
}
vector<bool> vis(n, false);
stack<int> st;
st.push(0);
vis[0] = true;
while (!st.empty()) {
    int t = st.top();
    st.pop();
    for (int a : adj[t]) {
        if (vis[a]) continue;
        st.push(a);
        vis[a] = true;
    }
}