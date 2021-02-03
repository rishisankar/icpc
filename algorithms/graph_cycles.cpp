// Detecting cycles in Directed Graphs

// detecting if each node can flow into a cycle: graphs/runningmom.cpp

// detecting if a cycle is present in a directed graph (NOT TESTED)
// want to recover the cycle? see https://cp-algorithms.com/graph/finding-cycle.html
// has_cycle(adj_list)

bool dfs(int v, vector<vector<int>> &adj, vector<int> &color) {
    color[v] = 1;
    for (int u : adj[v]) {
        if (color[u] == 0) {
            if (dfs(u))
                return true;
        } else if (color[u] == 1) {
            return true;
        }
    }
    color[v] = 2;
    return false;
}

void has_cycle(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<int> color(n, 0);

    for (int v = 0; v < n; v++) {
        if (color[v] == 0 && dfs(v, adj, color))
            return true;
    }
    return false;
}