/*
Find negative cycle in a graph
Returns empty list if no negative cycle, otherwise returns indices (ex: 1 2 4 1)
Complexity is same as Bellman-Ford: O(VE)
https://cp-algorithms.com/graph/finding-negative-cycle-in-graph.html
*/

struct Edge {
    int a, b;
    ll cost;
};

const ll INF = 1LL << 62;
VI find_negative_cycle(vector<Edge>& edges, int n) {
    int m = edges.size();
    vector<ll> d(n);
    vector<int> p(n, -1);
    int x;
    for (int i = 0; i < n; ++i) {
        x = -1;
        for (Edge e : edges) {
            if (d[e.a] + e.cost < d[e.b]) {
                d[e.b] = d[e.a] + e.cost;
                p[e.b] = e.a;
                x = e.b;
            }
        }
    }

    vector<int> cycle;
    if (x == -1) {
        return cycle;
    } else {
        for (int i = 0; i < n; ++i)
            x = p[x];
        vector<int> cycle;
        for (int v = x;; v = p[v]) {
            cycle.push_back(v);
            if (v == x && cycle.size() > 1)
                break;
        }
        reverse(cycle.begin(), cycle.end());
        return cycle;
    }
}
