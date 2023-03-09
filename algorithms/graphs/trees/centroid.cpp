/*
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
