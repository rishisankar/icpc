/*
Find all connected components in a undirected graph
(returns vector of nodes in each component)
Example: cses/graphs/building_roads
*/
VVI components(VVI adj) {
    int n = adj.size();
    vector<bool> vis(n,false);
    VVI comps;
    rep(i,0,n) {
        if (!vis[i]) {
            vis[i] = true;
            comps.resize(comps.size()+1);
            comps.back().pb(i);
            stack<int> s;
            s.push(i);
            while (!s.empty()) {
                int t = s.top(); s.pop();
                for (int x : adj[t]) {
                    if (vis[x]) continue;
                    vis[x] = true;
                    comps.back().pb(x);
                    s.push(x);
                }
            }
        }
    }
    return comps;
}

