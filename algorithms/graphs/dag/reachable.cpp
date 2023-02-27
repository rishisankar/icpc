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
Count number of pairs of nodes (x,y) s.t. x can reach y
O(n/64 * (n+m))
n = # nodes, m = # edges
dg = edge list in reverse topological order
*/
ll countReachablePairs(int n, int m, vector<pii>& dg) {
  ll ans = 0;
  vector<ull> mask(n);
  for (int l = 0; l < n; l += 64) {
    // process 64 at a time via bitmask: 
    int r = min(n, l + 64);
    rep(i,0,n) mask[i] = 0;
    for (int i = l; i < r; ++i) mask[i] = (1ull << (i-l));
    for (pii edge : dg) {
        mask[edge.F]|=mask[edge.S];
    }
    // for each of the n nodes, figure out how many of [l,r) is reachable
    rep(i,0,n)ans+=__builtin_popcountll(mask[i]);
  }
  return ans;
}


