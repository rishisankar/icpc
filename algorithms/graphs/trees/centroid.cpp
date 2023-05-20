/*
Build centroid tree from tree (adj). Store adjacency list in centroid_tree, parent 
pointers in par, root of tree in r (par[r] = -1).
Time: O(nlogn)

Root is centroid of original tree, then recurse...
Properties:
- Height of centroid tree is O(logn)
- Each subtree of centroid tree is a connected component in original tree
- LCA of two nodes in centroid tree is on path between two nodes in actual tree too

Example problem: two query types: color a vertex; find dist from vertex to closest colored vertex
Sol: let x be closest colored node to v. path must pass through lca(x,v), so only consider logn ancestors of v.

Tested on https://codeforces.com/problemset/problem/342/E
Based on: https://codeforces.com/blog/entry/81661
*/
void centroidDecomposition(VVI& adj, VVI& centroid_tree, VI& par, int& r) {
    int n = sz(adj);
    VB proc(n,0); // already processed (ie already found as a centroid)
    VI st_sz(n); // subtree size container
    function<void(int,int)> subtree_sz = [&](int t, int par) {
        st_sz[t] = 1;
        for (int x : adj[t]) {
            if (x != par && !proc[x]) {
                subtree_sz(x,t);
                st_sz[t] += st_sz[x];
            }
        }
    };
    function<int(int)> find_centroid = [&](int t) {
        subtree_sz(t,-1);
        int siz = st_sz[t];
        int prev = -1, cur = t;
        while (true) {
            int tv = -1;
            for (int x : adj[cur]) {
                if (x != prev && !proc[x]) {
                    if (st_sz[x] > siz/2) {
                        tv = x; break;
                    }
                }
            }
            if (tv != -1) {
                prev = cur;
                cur = tv;
            } else return cur;
        }
    };
    centroid_tree.resize(n);
    par.resize(n,-1);
    function<int(int)> build_ct = [&](int t) {
        int c = find_centroid(t);
        proc[c] = true;
        for (int x : adj[c]) {
            if (!proc[x]) {
                int cc = build_ct(x);
                centroid_tree[cc].pb(c);
                centroid_tree[c].pb(cc);
                par[cc] = c;
            }
        }
        return c;
    };
    r = build_ct(0);
}


/*
find all centroids:

Centroid decomposition on a tree (can find 1-2 centroids; if 2 the centroids are connected)
1 vs 2 centroids depends on parity o fthe 
Centroid means all subtrees have at most floor(n/2) nodes.
Returns 1-2 nodes [0-n) representing the centroids
https://codeforces.com/blog/entry/57593
tested on cses/trees/finding_a_centroid, cses/additional/tree_isomorphism2
*/
vector<int> findCentroids(vector<vector<int>>& g) {
    int n = g.size();
    vector<int> centroid;
    vector<int> siz(n); // stores size of each subtree
    function<void (int,int)> dfs = [&](int u, int prev) {
        siz[u] = 1;
        bool is_centroid = true;
        for (auto v : g[u]) if (v!=prev) {
            dfs(v,u);
            siz[u] += siz[v]; // update siz from children subtrees
            if (siz[v] > n/2) is_centroid = false; // subtree too big
        }
        if (n-siz[u] > n/2) is_centroid = false; // consider subtree going through parent
        if (is_centroid) centroid.push_back(u);
    };
    dfs(0,-1);
    return centroid;
}
