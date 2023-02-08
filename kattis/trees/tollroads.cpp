#include <bits/stdc++.h>
using namespace std;

#define FOR(i, j, k) for (int i=j ; i<k ; ++i)
#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define FORI(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k) for (int i=j ; i>=k ; --i)
#define RFORI(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j)
#define RREP(i, j) RFOR(i, j, 0)
#define OREP(i, j) FOR(i, 1, j+1)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
#define F first
#define S second
#define INP(v, n) for (int i=0; i<n; ++i) { cin >> v[i]; }
#define ceil(x) (ll)ceil(x)
#define floor(x) (ll)floor(x)

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

template<typename T> inline void printV(vector<T> &vec) {
    cerr << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        cerr << vec[i] << ' ';
    }
    cerr << '\n';
    cerr << "########\n";
}
template<typename T> inline void printVV(vector<vector<T>> &vec) {
    cerr << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            cerr << vec[i][j] << ' ';
        }
        cerr << '\n';
    }
    cerr << "########\n";
}
template<typename T> inline void print(T obj) { cout << obj << '\n'; }
template<typename T, typename... Args> inline void print(T t, Args... args) { cout << t << " "; print(args...); }
template<typename T> inline void dbg(T obj) { cerr << obj << '\n'; }
template<typename T, typename... Args> inline void dbg(T t, Args... args) { cerr << t << " "; dbg(args...); }

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
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;

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

// To create: DSU d(capacity)
// remember to add elts (between 0 and capacity)
// O(log(n)) complexity for both finds/unions

struct DSU {

    vector<int> parent, rank;
    int elts;
    int sz;

    DSU (int x) {
		parent.resize(x+1);
        rank.resize(x+1);
        elts = 0;
        sz = 0;
		fill(parent.begin(), parent.end(), -1);
	}

    /**
     * Adds v (in a new set) to the DSU
     */
    void make_set(int v) {
        if (parent[v] == -1) { ++elts; ++sz; }
        parent[v] = v;
        rank[v] = 1;
    }

    /**
     * Finds the sets containing v
     */
    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    /**
     * Unions the sets containing elements a and b
     */
    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            rank[a] += rank[b];
            --sz;
        }
    }

    int elements() {
        return elts;
    }

    int size() {
        return sz;
    }

    void clear() {
        fill(parent.begin(), parent.end(), -1);
        elts = 0;
        sz = 0;
    }

    /**
     * Adds all integers in (inclusive) range [first, last] to DSU
     */
    void add_range(int first, int last) {
        for (int i = first; i <= last; ++i) {
            make_set(i);
        }
    }

    /**
     * Returns size of the set containing v (assuming in v)
     */
    int set_size(int v) {
        return rank[find_set(v)];
    }

    bool contains(int v) {
        return parent[v] != -1;
    }

};


struct Edge {
    int u, v, weight;
    Edge (int u_, int v_, int w_) : u(u_), v(v_), weight(w_) {}
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

int kruskal(int n, vector<Edge>& edges, vector<Edge>& result) {
    int cost = 0;
    DSU ds(n);
    for (int i = 0; i < n; i++) ds.make_set(i);
    sort(edges.begin(), edges.end());
    for (Edge e : edges) {
        if (ds.find_set(e.u) != ds.find_set(e.v)) {
            cost += e.weight;
            result.push_back(e);
            ds.union_sets(e.u, e.v);
        }
    }
    return cost;
}


/*

process edges (u,v,c) of mst in sorted order (create full binary tree with n-1 internals)

- add node N to tree connecting head[u], head[v], store cost[N] = c
- union(u,v) in DSU
- set head[union(u,v)] = N

To do query 1(a,b): return cost[lca(a,b)]


process edges (u,v,c) of mst in sorted order.
- union(u,v) in DSU

To do query 2(a,b): return set size after adding all edges of corresponding cost

*/

void run() {
    int n, m, q; cin >> n >> m >> q;
    vector<Edge> edges_premst;
    REP(i, m) {
        int u,v,t;
        cin >> u >> v >> t;
        --u; --v;
        edges_premst.PB(Edge(u,v,t));
    }
    vector<Edge> edges;
    kruskal(n, edges_premst, edges);  // num edges should be n-1, edges in sorted order.
    VPII qs(q);
    REP(i, q) {
        cin >> qs[i].F >> qs[i].S;
        --qs[i].F;
        --qs[i].S;
    }

    // solve query 1
    DSU d1(n);
    d1.add_range(0,n-1);
    unordered_map<int,int> heads;
    REP(i,n) {
        heads[d1.find_set(i)] = i + n-1;
    }
    VVI btree(2*n-1);
    VI costs(n-1);
    // nodes [n-1...2n-2] correspond to city 0...n-1
    // nodes [0..n-2] correspond to n-1 internals, alloc from the back
    REP(i, n-1) {
        // node in btree: n-2-i
        btree[n-2-i].PB(heads[d1.find_set(edges[i].u)]);
        btree[n-2-i].PB(heads[d1.find_set(edges[i].v)]);
        costs[n-2-i] = edges[i].weight;
        d1.union_sets(edges[i].u, edges[i].v);
        heads[d1.find_set(edges[i].u)] = n-2-i;
    }
    LCA lca(btree);
    VI q1(q);
    REP(i, q) {
        q1[i] = costs[lca.lca(qs[i].F + n-1, qs[i].S + n-1)];
    }

    // solve query 2
    VI q2(q);
    DSU d2(n);
    d2.add_range(0,n-1);
    vector<tuple<int, pii, int>> qwd;
    REP(i, q) {
        qwd.PB({q1[i], qs[i], i});
    }
    sort(all(qwd));
    int qp = 0;
    REP(i, n-1) {
        d2.union_sets(edges[i].u, edges[i].v);
        if (i == n-2 || edges[i+1].weight > edges[i].weight) {
            // added all edges for weight edges[i].weight
            while (qp < q && get<0>(qwd[qp]) == edges[i].weight) {
                // solve corresponding query
                q2[get<2>(qwd[qp])] = d2.set_size(get<1>(qwd[qp]).F);
                ++qp;
            }
        }
    }

    REP(i,q) {
        print(q1[i],q2[i]);
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    // ll t; cin >> t;
    ll t=1;
    REP(tests,t) run();
}