/*
O(nlog^2n) approach for offline dynamic connectivity.
O(nlogn) is possible (with bigger constant factor?): link cut tree + maximal spanning tree
This approach is based on https://cp-algorithms.com/data_structures/deleting_in_log_n.html

Returns # of components after each event (0th index = before any events).
Event is either add (if not exist) / remove (if exist) edge {a,b}.
G is the initial list of edges (no dups allowed)

Assumes no duplicate edges or invalid deletions

(depends on kactl/data-structures/UnionFindRollback - modified to give # comps)
tested on cses/advanced/dynamic_connectivity
*/
struct RollbackUF {
    int nc; // # comps
	vi e; vector<pii> st;
	RollbackUF(int n) : nc(n), e(n, -1) {}
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : find(e[x]); }
	int time() { return sz(st); }
	void rollback(int t) {
		for (int i = time(); i --> t;) {
			e[st[i].first] = st[i].second;
        }
        nc += (time()-t)/2;
		st.resize(t);
	}
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
        --nc;
		if (e[a] > e[b]) swap(a, b);
		st.push_back({a, e[a]});
		st.push_back({b, e[b]});
		e[a] += e[b]; e[b] = a;
		return true;
	}
    int comps() { return nc; }
};

vi dynacon(int n, vector<pii> G, vector<pii> events) {
    int n_ev = sz(events), m = sz(G);
    // make edges have a<b property (for map)
    rep(i,0,m) if (G[i].F > G[i].S) swap(G[i].F,G[i].S);
    rep(i,0,n_ev) if (events[i].F > events[i].S) swap(events[i].F,events[i].S);
    // figure out how long each event is "alive" for
    vector<pair<pii,pii>> alive; // first pii = edge, second pii [t,s] = active from time t to time s
    map<pii, int> active; // active edges
    rep(i,0,m) active[G[i]] = 0;
    rep(i,0,n_ev) {
        auto it = active.find(events[i]);
        if (it != active.end()) { // edge exists --> del
            alive.pb({events[i], {it->S,i}});
            active.erase(it);
        } else {
            active[events[i]] = i+1;
        }
    }
    // remaining edges
    for (auto p : active) alive.pb({p.F, {p.S, n_ev}});
    // construct segtree
    vector<vector<pii>> st(4*n_ev+8); // segtree over [0 ... n_ev]
    function<void(int,int,int,int,int,pii)> addST = [&](int v, int lo, int hi, int l, int r, pii ed) {
        if (r < lo || l > hi) return;
        if (l <= lo && hi <= r) {
            st[v].pb(ed);
            return;
        }
        int mid = (lo+hi)/2;
        addST(2*v,lo,mid,l,r,ed);
        addST(2*v+1,mid+1,hi,l,r,ed);
    };
    rep(i,0,sz(alive)) addST(1,0,n_ev,alive[i].S.F,alive[i].S.S,alive[i].F);
    // run dfs to compute answers
    vi ans(n_ev+1); // +1 to store # comps before first event
    RollbackUF dsu(n);
    function<void(int,int,int)> dfs = [&](int v, int lo, int hi) {
        // add all edges
        int tm = dsu.time();
        for (pii ed : st[v]) {
            dsu.join(ed.F, ed.S);
        }
        if (lo==hi) {
            ans[lo] = dsu.comps();
        } else {
            int mid = (lo+hi)/2;
            dfs(2*v,lo,mid);
            dfs(2*v+1,mid+1,hi);
        }
        dsu.rollback(tm);
    };
    dfs(1,0,n_ev);
    return ans;
}
