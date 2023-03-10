/*
Root a tree at node r. Returns {childs, parent}. O(n)
*/
pair<vector<vi>,vi> rootTree(vector<vi>& adj, int r) {
    int n = adj.size();
    vector<vi> childs(n);
    vi parent(n);
    vector<bool> visited(n,false);
    stack<int> s;
    s.push(r);
    visited[r] = true;
    parent[r] = -1;
    while (!s.empty()) {
        int t = s.top();
        s.pop();
        for (int x : adj[t]) {
            if (visited[x]) continue;
            parent[x] = t;
            childs[t].push_back(x);
            visited[x] = true;
            s.push(x);
        }
    }
    return {childs,parent};
}

/*
Convert tree to array with each subtree contiguous (DFS)
Return vector<pii> d(n), where d[i] = {a,b} indicates 
subtree rooted at node i is at indices [a,b) of the array.
(root of subtree always at index a)
Time: O(n)
Tested on cses/trees/subtree_queries
*/
vector<pii> subtreeArrayDecomp(VVI& adj, int root) {
    int n = adj.size();
    int ct = 0;
    vector<pii> decomp(n);
    function<void (int,int)> dfs = [&](int t, int p) {
        decomp[t].F = ct++;
        for (int x : adj[t]) {
            if (x == p) continue;
            dfs(x,t);
        }
        decomp[t].S = ct;
    };
    dfs(root,-1);
    return decomp;
}
