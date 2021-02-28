/**
 * Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/graph/Dinic.h
 * Flow algorithm with complexity O(VE logU) where U = max(cap)
 * O(min(E^{1/2}, V^{2/3}) * E) if U = 1
 * O(sqrt(V) * E) for bipartite matching.
 * To use: (see example regionals/ridehailing.cpp)
 *      Dinic flow_graph(n); <- n = number of vertices
 *      flow_graph.addEdge(start, end, capacity, [required_capacity??])
 *      flow_graph.calc() tells you max flow
 * 
 * 
 * Applications of max flow:
 *      - minimum path cover - minimum # of paths that cover all vertices (https://walkccc.me/CLRS/Chap26/Problems/26-2/)
 *      - maximum bipartite matching
 */

struct Dinic {
	struct Edge {
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vi lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, ll rcap = 0) {
		adj[a].push_back({b, sz(adj[b]), c, c});
		adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < sz(adj[v]); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		rep(L,0,31) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vi(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (Edge e : adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};
