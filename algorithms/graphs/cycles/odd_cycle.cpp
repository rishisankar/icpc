// idea: equivalent to checking whether or not a graph is bipartite
// odd cycle := cycle containing odd number of vertices
// color each vertex either 1 or 2, if you try to recolor a vertex then there's an odd cycle

// given: undirected graph (adjacency list)
// example: cses/graphs/building_teams

bool hasOddCycle(vector<vector<int>> adj) {
    int n = adj.size();
    vector<int> colors(n, 0);

    for (int i = 0; i < n; ++i) {
        if (colors[i] != 0) continue;
        stack<pair<int,int>> s;
        s.push({i,1});
        while(!s.empty()) {
            int t = s.top().first;
            int c = s.top().second;
            s.pop();
            if (colors[t] != 0) {
                if (colors[t] != c) {
                    return true;
                }
            } else {
                colors[t] = c;
                int nc = (c%2)+1;
                for (int a : adj[t]) {
                    s.push({a, nc});
                }
            }
        }
    }

    return false;
}
