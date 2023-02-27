struct Graph {
  int n,m;
  bool isDirected;
  vector<vector<int>> adj;
  Graph(int n, int m, bool isDirected=false)
    : n(n), m(m), isDirected(isDirected) {
    adj.resize(n);
  }

  void addEdge(int a, int b) {
    if (!isDirected) adj[b].push_back(a);
    adj[a].push_back(b);
  }

  void readEdges(bool zeroIndexed) {
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        if (!zeroIndexed) {
            --a; --b;
        }
        addEdge(a,b);
    }
  }

  /* run dfs: fn as [&](int x) {} */
  void dfs(int start, function<bool(int)> fn) {
    vector<bool> vis(n, false);
    stack<int> st;
    st.push(start);
    vis[start] = true;
    while (!st.empty()) {
        int t = st.top();
        st.pop();
        if (fn(t)) {
            for (int a : adj[t]) {
                if (vis[a]) continue;
                st.push(a);
                vis[a] = true;
            }
        }
    }
  }
};
