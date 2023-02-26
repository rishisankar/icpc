// kattis teamchange
// max ind set / min vertex cover

struct Edge {
  int to, rev;
  ll c, oc;
  ll flow() { return max(oc - c, 0LL); } // if you need flows
};

struct Dinic {
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

void solve() {
  // # of nodes in left half, right half of graph
  int L, R;
  int N = L+R+2;
  // nodes 0..{L-1} for left nodes, nodes L..{L+R-1} for right, nodes L+R, L+R+1 for s/t
  Dinic d(N);

  // add edges to dinic for matching (with capacity 1)

  ll res = d.calc(L+R,L+R+1);

  // next construct new graph to figure out max ind set
  vector<vector<int>> adj(L+R);
  unordered_set<int> unmatched;
  rep(i,0,L) {
    bool matched = false;
    for (Edge e : d.adj[i]) {
      if (e.to == L+R) continue;
      if (e.flow() == 0) {
        adj[i].pb(e.to);
      } else {
        dbg(i,e.to);
        matched = true;
        adj[e.to].pb(i);
      }
    }
    if (!matched) unmatched.insert(i);
  }

  // run dfs
  unordered_set<int> visited;
  stack<int> st;
  for (int x : unmatched) {
    st.push(x);
    visited.insert(x);
  }
  while (!st.empty()) {
    int t = st.top();
    st.pop();
    for (int x : adj[t]) {
      if (visited.count(x)) continue;
      st.push(x);
      visited.insert(x);
    }
  }
  
  // maxIS = visited stuff on left + unvisited stuff on right
  // note that min vertex cover is the complement
  unordered_set<int> maxIS;
  rep(i,0,L) {
    if (visited.count(i)) maxIS.insert(i);
  }
  for (int i = L; i < L+R; ++i) {
    if (!visited.count(i)) maxIS.insert(i);
  }
}
