#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define FOR(i, j, k) for (int i=j ; i<k ; ++i)
#define FORI(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k) for (int i=j ; i>=k ; --i)
#define RFORI(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j)
#define RREP(i, j) RFOR(i, j, 0)
#define OREP(i, j) FOR(i, 1, j+1)
#define all(cont) cont.begin(), cont.end()
#define PB push_back

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

typedef long long ll;
typedef long double ld;
typedef vector<int> VI;
typedef vector<vector<int>> VVI;
typedef vector<bool> VB;
typedef vector<vector<bool>> VVB;
typedef vector<string> VS;
typedef vector<vector<string>> VVS;
typedef pair<int, int> PII;

// Kruskal's Algorithm for minimum spanning trees
// uses a DSU for efficiency
// example: trees/lostmap.cpp

// int kruskal(n, edges, result)
// n: # of vertices
// vector<Edge> edges: contains all edges in graph
// vector<Edge> result: empty list to add only mst edges to
// return: minimum cost 

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


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.setf(ios::fixed);
    cout.precision(10);

    int t; cin >> t;
    REP(tests, t) {
        vector<Edge> edges,res;
        int n; cin >> n;
        vector<pair<ld,ld>> v;
        REP(i, n) {
            ld x,y; cin >> x >> y;
            v.PB({x,y});
        }
        REP(i, n) {
            FOR(j, i+1, n) {
                ld dx = v[i].first - v[j].first;
                ld dy = v[i].second - v[j].second;
                ld dist = sqrt(dx*dx+dy*dy);
                Edge e(i,j,dist);
                edges.PB(e);
            }
        }
        cout << kruskal(n, edges, res) << '\n';
    }

}