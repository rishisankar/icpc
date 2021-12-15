#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
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
#define INP(v, n) for (int i=0; i<n; ++i) { cin >> v[i]; }
#define ceil(x) (ll)ceil(x)
#define floor(x) (ll)floor(x)

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

template<typename T> inline void printV(vector<T> &vec) {
    cout << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << ' ';
    }
    cout << '\n';
    cout << "########\n";
}
template<typename T> inline void printVV(vector<vector<T>> &vec) {
    cout << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            cout << vec[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << "########\n";
}
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
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

// Kruskal's Algorithm for minimum spanning trees
// uses a DSU for efficiency
// example: trees/lostmap.cpp, jurassicjigsaw.cpp, islandhopping.cpp

// int kruskal(n, edges, result)
// n: # of vertices
// vector<Edge> edges: contains all edges in graph (edge indices are ordered 0 to n-1)
// vector<Edge> result: empty list to add only mst edges to
// return: minimum cost 

// important: to change cost to long/double/whatever, 4 changes required:
// - weight/constructor of Edge struct, cost/return of kruskal function

// time: O(M log N)

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
    int u, v; ll weight;
    Edge (int u_, int v_, ll w_) : u(u_), v(v_), weight(w_) {}
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

ll kruskal(int n, vector<Edge>& edges, vector<Edge>& result) {
    ll cost = 0;
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
    if (ds.size() != 1) {
        return LLONG_MAX;
    }
    return cost;
}

void run() {
    ll n, m;
    while (true) {
        cin >> n >> m;
        if (n == 0 && m == 0) return;
        vector<Edge> edges;
        REP(i, m) {
            int u, v; ll w;
            cin >> u >> v >> w;
            Edge e(u,v,w);
            edges.PB(e);
        }
        vector<Edge> res;
        ll r = kruskal(n,edges,res);
        if (r == LLONG_MAX) {
            print("Impossible");
        } else {
            print(r);
            VPII pe;
            for (Edge e : res) {
                pe.push_back({min(e.u,e.v), max(e.u,e.v)});
            }
            sort(all(pe));
            for (PII p : pe) {
                print(p.first,p.second);
            }
        }
    }    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);
    // ll t; cin >> t;
    ll t=1;
    REP(tests,t) run();
}