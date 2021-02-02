#include <bits/stdc++.h>
using namespace std;

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

int main() {
    int n, K;
    cin >> n >> K;

    vector<vector<int>> inp(n, vector<int>(n));
    vector<bool> completed(n+1, false);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> inp[i][j];
            if (inp[i][j] != 0) completed[inp[i][j]] = true;
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (completed[i]) continue;
        vector<vector<int>> adj_list(n+1); // row -> col

        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                if (inp[j-1][k-1] == 0) {
                    adj_list[j].push_back(k);
                }
            }
        }

        vector<int> matches(n+1);
        int mat = hopcroftkarp(adj_list, matches, n, n);
        if (mat != n) {
            cout << "NO\n";
            exit(0);
        }

        for (int j = 1; j <= n; ++j) {
            inp[j-1][matches[j]-1] = i;
        }
    }

    cout << "YES\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << inp[i][j] << " ";
        }
        cout << '\n';
    }

}