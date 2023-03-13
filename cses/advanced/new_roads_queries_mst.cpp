#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define INP(v, n) for (int i=0; i<n; ++i) { cin >> v[i]; }
#define ceil(x) (ll)ceil(x)
#define floor(x) (ll)floor(x)

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) 
{ os << '{'; string sep; for (const auto &x: v) os << sep << x, sep = ", "; return os << '}';}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) 
{ return os << '(' << p.first << ", " << p.second << ')'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

template<typename T> inline void print(T obj) { cout << obj << '\n'; }
template<typename T, typename... Args> inline void print(T t, Args... args) { cout << t << " "; print(args...); }

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef vector<int> VI;
typedef vector<int> vi; 
typedef vector<vector<int>> VVI;
typedef vector<long long> VLL;
typedef vector<vector<long long>> VVLL;
typedef vector<bool> VB;
typedef vector<vector<bool>> VVB;
typedef vector<string> VS;
typedef vector<vector<string>> VVS;
typedef pair<int, int> PII;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

VPII dirs{mp(-1,0),mp(1,0),mp(0,-1),mp(0,1)};
const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
// const ll mod = 998244353;

/*
Find all connected components in a undirected graph
(returns vector of nodes in each component)
Example: cses/graphs/building_roads
*/
VVI components(VVI adj) {
    int n = adj.size();
    vector<bool> vis(n,false);
    VVI comps;
    rep(i,0,n) {
        if (!vis[i]) {
            vis[i] = true;
            comps.resize(comps.size()+1);
            comps.back().pb(i);
            stack<int> s;
            s.push(i);
            while (!s.empty()) {
                int t = s.top(); s.pop();
                for (int x : adj[t]) {
                    if (vis[x]) continue;
                    vis[x] = true;
                    comps.back().pb(x);
                    s.push(x);
                }
            }
        }
    }
    return comps;
}

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

/*
Given a tree with n-1 weighted edges, for each query (u,v) determine the
max edge weight on path from u to v (uses reachability tree)
Easy to modify to sum / min / etc
Complexity: O(N + Qlogn)

Technique similar to: https://codeforces.com/blog/entry/85714
Depends on kactl/data_structures/UnionFind, kactl/graph/LCA
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

void run() {
    int n,m,q; cin >> n >> m >> q;
    vector<Edge> edges;
    VVI adj(n);
    rep(i,0,m) {
        int a,b; cin >> a >> b; --a; --b;
        Edge e; e.u=a; e.v=b; e.w=i+1;
        edges.pb(e);
        adj[a].pb(b);
        adj[b].pb(a);
    }
    // first, break into each component
    VVI comps = components(adj);
    VPII compMap(n); // maps each node to {comp id, index in comp}
    rep(i,0,comps.size()) {
        int ct = 0;
        for (int x : comps[i]) {
            compMap[x] = {i,ct++};
        }
    }
    vector<vector<Edge>> compEdges(comps.size());
    for (Edge e: edges) {
        int c = compMap[e.u].F;
        e.u = compMap[e.u].S;
        e.v = compMap[e.v].S;
        compEdges[c].pb(e);
    }
    vector<vector<pair<pii,int>>> queries(comps.size());
    vector<int> ans(q,-1);
    rep(i,0,q) {
        int a,b; cin >> a >> b; --a; --b;
        if (a==b) {
            ans[i]=0;
            continue;
        }
        int c = compMap[a].F;
        int c2 = compMap[b].F;
        if (c == c2) {
            a = compMap[a].S; b = compMap[b].S;
            queries[c].pb({{a,b},i});
        }
    }
    rep(i,0,comps.size()) {
        sort(all(compEdges[i]), [&](Edge& e1, Edge& e2) {
            return e1.w < e2.w;
        });
        UF dsu(comps[i].size());
        vector<Edge> mst;
        for (Edge& e : compEdges[i]) {
            if (dsu.find(e.u) == dsu.find(e.v)) continue;
            mst.pb(e);
            dsu.join(e.u,e.v);
        }
        maxEdgeWeightQueries(mst, queries[i], ans);
    }
    for (int i : ans) print(i);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    // ll t; cin >> t;
    ll t=1;
    rep(tests,0,t) run();
}