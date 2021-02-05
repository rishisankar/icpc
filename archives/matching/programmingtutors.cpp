#include <bits/stdc++.h>
using namespace std;


typedef long long ll;

// Hopcroft-Karp-Karzanov algorithm for maximum bipartite matching

// IMPORTANT: number vertices starting with 1, vertex 0 is reserved for use by algorithm

// main function: hopcroftkarp(adj_list, matches, L, R)
// adj_list (size L+1) should represent connected vertices in right set for each in set 1
// L = size of set 1, R = size of set 2
// matches (size L+1) will contain final match of each vertex in left set (or 0 if no match).

// source: https://www.geeksforgeeks.org/hopcroft-karp-algorithm-for-maximum-matching-set-2-implementation/

// examples: graphs/bookclub_hkk, graphs/historicexhibition

// checks if there is an augmenting path, update distances for later reference by dfs
bool hkk_bfs(vector<vector<int>>& adj_list, int L, int R, vector<int>& left_match, vector<int>& right_match, vector<int>& dist) {
    queue<int> q;

    // setup queue and initialize distances
    for (int i = 1; i <= L; ++i) {
        if (left_match[i] == 0) {
            dist[i] = 0;
            q.push(i);
        } else {
            dist[i] = INT_MAX;
        }
    }
    dist[0] = INT_MAX;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (dist[u] < dist[0]) {
            for (int v : adj_list[u]) {
                int cur_match = right_match[v];
                if (dist[cur_match] == INT_MAX) {
                    dist[cur_match] = dist[u] + 1;
                    q.push(cur_match);
                }
            }
        }
    }

    return dist[0] != INT_MAX;

}

bool hkk_dfs(int u, vector<vector<int>>& adj_list, vector<int>& left_match, vector<int>& right_match, vector<int>& dist) {
    if (u == 0) return true;

    for (int v : adj_list[u]) {
        int cur_match = right_match[v];
        if (dist[cur_match] == dist[u] + 1) {
            if (hkk_dfs(cur_match, adj_list, left_match, right_match, dist)) {
                left_match[u] = v;
                right_match[v] = u;
                return true;
            }
        }
    }

    dist[u] = INT_MAX;
    return false;
}

int hopcroftkarp(vector<vector<int>>& adj_list, vector<int>& matches, int L, int R) {
    vector<int> left_match(L+1, 0);
    vector<int> right_match(R+1, 0);
    vector<int> dist(L+1, 0); // dist along an augmenting path (calculated using bfs)

    int total = 0;

    while (hkk_bfs(adj_list, L, R, left_match, right_match, dist)) {
        for (int i = 1; i <= L; ++i) {
            if (left_match[i] == 0 && hkk_dfs(i, adj_list, left_match, right_match, dist)) {
                ++total;
            }
        }
    }

    for (int i = 1; i <= L; ++i) {
        if (left_match[i] != 0 && right_match[left_match[i]] == i) {
            matches[i] = left_match[i];
        } else {
            matches[i] = 0;
        }
    }

    return total;
}

struct edge {
    int s;
    int t;
    ll weight;
};

bool compare(edge e1, edge e2) {
    return (e2.weight > e1.weight);
}

int main() {
    int n;
    cin >> n;
    vector<ll> sx(n);
    vector<ll> sy(n);
    for  (int i = 0; i < n; ++i) {
        cin >> sx[i] >> sy[i];
    }

    vector<edge> edges(n*n);

    for (int i = 0; i < n; ++i) {
        ll x, y;
        cin >> x >> y;
        for (int j = 0; j < n; ++j) {
            ll cost = abs(x - sx[j]) + abs(y - sy[j]);
            edges[i*n+j].weight = cost;
            edges[i*n+j].s = j+1;
            edges[i*n+j].t = i+1;
        }
    }

    sort(edges.begin(), edges.end(), compare);

    // for (edge i : edges) {
    //     cout << i.s << ' ' << i.t << ' ' << i.weight << '\n';
    // }

    ll lo = 0;
    ll hi = 1000000000LL;
    ll best = hi;
    while (lo <= hi) {

        ll mid = (lo + hi) / 2;

        vector<vector<int>> adj(n+1);
        for (edge e : edges) {
            if (e.weight > mid) break;
            adj[e.s].push_back(e.t);
        }

        vector<int> matches(n+1);

        if (hopcroftkarp(adj, matches, n, n) == n) {
            best = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }


    }

    cout << best <<'\n';


}