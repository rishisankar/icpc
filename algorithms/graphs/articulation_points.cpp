/*
articulationPoints(VVI adj) on an undirected graph returns all articulation points
(i.e. points that if removed along with incident edges causes a disconnect)
based on: https://cp-algorithms.com/graph/cutpoints.html#implementation
tested on: cses/advanced/necessary_cities

for bridges: cses/advanced/necessary_roads (template on kactl/graphs/BiconnectedComponents)
*/

vector<int> tin, low;
int timer;
void dfs(int t, int p, VVI& adj, unordered_set<int>& ap) {
    tin[t] = low[t] = timer++;
    int ct = 0;
    for (int x : adj[t]) {
        if (x==p) continue;
        if (tin[x] == -1) {
            // dfs to children (they compute low first)
            dfs(x,t,adj,ap);
            low[t] = min(low[t], low[x]);
            // if a child depends only on t
            if (low[x] >= tin[t] && p!=-1) ap.insert(t);
            ++ct;
        } else {
            // back-edge to ancestor in DFS tree
            low[t] = min(low[t], tin[x]);
        }
    }
    if (p == -1 && ct >= 2) {
        // root node: articulation if multiple children
        ap.insert(t);
    }
}

unordered_set<int> articulationPoints(VVI& adj) {
    int n = adj.size();
    tin.resize(n,-1);
    low.resize(n);
    timer = 0;
    unordered_set<int> ap;
    rep(i,0,n) {
        if (tin[i] == -1) {
            dfs(i,-1,adj,ap);
        }
    }
    return ap;
}
