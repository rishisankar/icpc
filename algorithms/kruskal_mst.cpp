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
