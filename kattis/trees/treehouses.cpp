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
template<typename T, typename... Args> inline void dbg(T t, Args... args) { cerr << t << " "; print(args...); }

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
    int u, v;
    ld weight;
    Edge (int u_, int v_, ld w_) : u(u_), v(v_), weight(w_) {}
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

ld kruskal(int n, vector<Edge>& edges, vector<Edge>& result) {
    ld cost = 0;
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

void run() {
    int n, e, p;
    cin >> n >> e >> p;

    vector<vector<ld>> v(n, vector<ld>(2));
    vector<vector<bool>> adj(n, vector<bool>(n, false));
    REP(i, n) {
        cin >> v[i][0] >> v[i][1];
    }

    REP(i, p) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a][b] = adj[b][a] = true;
    }

    int N = n*(n-1)/2;
    vector<Edge> ed;

    REP(i, n) {
        for (int j = i+1; j < n; ++j) {
            if ((i < e && j < e) || adj[i][j]) {
                Edge ege(i,j,0);
                ed.PB(ege);
            } else {
                ld dx = v[i][0] - v[j][0];
                ld dy = v[i][1] - v[j][1];
                ld wt = sqrt(dx*dx + dy*dy);
                Edge ege(i,j,wt);
                ed.PB(ege);
            }
        }
    }

    vector<Edge> res;
    ld xxx = kruskal(N, ed, res);

    cout << xxx << '\n';




}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    cout.setf(ios::fixed);
    cout.precision(15);
    // ll t; cin >> t;
    ll t=1;
    REP(tests,t) run();
}