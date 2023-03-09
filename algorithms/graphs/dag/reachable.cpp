/*
Solution O(n*(n+m))
Output: vvb reach[v][u] = 1 if u reachable from v
0) initialize reach[v][v] = 1 for all v
1) iterate over edges (v->u) in reverse topological order
  reach[v] = reach[v] | reach[u] (bitwise)

Optimizations:
- use an edge list instead of adj list (unrolling)
- use ull's to store batches of 64 for 64x speedup in bitwise or
*/

/*
Count number of nodes reachable from each node
Returns vector v (v[i] = # nodes reachable from i, including i itself)
O(n/64 * (n+m))
n = # nodes, m = # edges
dg = edge list in reverse topological order
Example: cses/advanced/reachable_nodes (can also look at cses/advanced/reachability_queries)
*/

#pragma GCC target("popcnt")
vi countReachable(int n, int m, vector<pii>& dg) {
  vector<ull> mask(n);
  vector<int> ans(n,0);
  for (int l = 0; l < n; l += 64) {
    // process 64 at a time via bitmask: 
    int r = min(n, l + 64);
    rep(i,0,n) mask[i] = 0;
    for (int i = l; i < r; ++i) mask[i] = (1ull << (i-l));
    for (pii edge : dg) {
        mask[edge.F]|=mask[edge.S];
    }
    // for each of the n nodes, figure out how many of [l,r) is reachable
    rep(i,0,n)ans[i]+=__builtin_popcountll(mask[i]);
  }
  return ans;
}


/*
To construct reverse topological ordering:
(create radj then run kactl toposort)
O(n+m)
*/
vi topoSort(const vector<vi>& gr) {
	vi indeg(sz(gr)), ret;
	for (auto& li : gr) for (int x : li) indeg[x]++;
	queue<int> q; // use priority_queue for lexic. largest ans.
	rep(i,0,sz(gr)) if (indeg[i] == 0) q.push(i);
	while (!q.empty()) {
		int i = q.front(); // top() for priority queue
		ret.push_back(i);
		q.pop();
		for (int x : gr[i])
			if (--indeg[x] == 0) q.push(x);
	}
	return ret;
}
vector<pii> edgesInReverseTopo(vector<vi>& radj) {
    int n = radj.size();
    vi ts = topoSort(radj);
    vector<pii> edges;
    for (int i : ts) {
        for (int j : radj[i]) edges.pb({j,i});
    }
    return edges;
}

