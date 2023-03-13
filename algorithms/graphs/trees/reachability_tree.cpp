/*
Reachability tree: https://codeforces.com/blog/entry/85714

Idea: create tree with 2n-1 nodes for each of the original nodes + (n-1) nodes of tree
By adding edges in specific order, can answer queries on subtree based on edge adding order (or deleting, go in reverse)
Can also solve problems asking for min/max edge weight on path (see template below)
*/


/*
Given a tree with n-1 weighted edges, for each query (u,v) determine the
max edge weight on path from u to v (uses reachability tree)
Easy to modify to min / other stuff
Complexity: O(N + Qlogn)
Queries structure: {{u,v},i} --> stored in answers[i]

Depends on kactl/data_structures/UnionFind, kactl/graph/LCA (included below)
*/
struct Edge {
    int u,v;
    ll w;
};

void maxEdgeWeightQueries(vector<Edge>& edges, vector<pair<pii,int>> queries, vector<int>& answers) {
    int n = edges.size()+1, q = queries.size();
    sort(all(edges),[&](Edge& e1, Edge& e2) { // edges should be in decreasing order for max query
        return e1.w > e2.w;
    });
    // construct reachability binary tree (0-{n-2} for edges, {n-1}-{2n-2} for nodes)
    UF vertDSU(n); // stores which nodes are connected already
    vector<int> vertMap(n); // stores top actual node for each dsu set
    rep(i,0,n) vertMap[i] = n-1+i;
    vector<vector<int>> rt(2*n-1); //reachability tree (directed, rooted at 0)
    vector<ll> weights(n-1); // stores min in subtree for each set of nodes
    rep(i,0,n-1) weights[i] = edges[i].w;
    for (int j = n-2; j >= 0; --j) {
        Edge e = edges[j];
        int nd1 = vertMap[vertDSU.find(e.u)];
        int nd2 = vertMap[vertDSU.find(e.v)];
        rt[j].pb(nd1);
        rt[j].pb(nd2);
        vertDSU.join(e.u, e.v);
        vertMap[vertDSU.find(e.u)] = j;
    } 
    LCA lca(rt);
    rep(i,0,q) {
        answers[queries[i].S] = weights[lca.lca(queries[i].F.F + n-1, queries[i].F.S + n-1)];
    }
}


// KACTL dependencies below for convenience:

struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

struct LCA {
	int T = 0;
	vi time, path, ret;
	RMQ<int> rmq;

	LCA(vector<vi>& C) : time(sz(C)), rmq((dfs(C,0,-1), ret)) {}
	void dfs(vector<vi>& C, int v, int par) {
		time[v] = T++;
		for (int y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
			dfs(C, y, v);
		}
	}

	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
	//dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};