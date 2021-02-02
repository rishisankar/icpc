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
    int n, k;
    cin >> n >> k;

    vector<vector<int>> inp(n, vector<int>(n, 0));

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> inp[i][j];
        }
    }

    for (int i = 0; i < k; ++i) {
        vector<bool> visited(n+1,false);
        for (int j = 0; j < n; ++j) {
            if (visited[inp[i][j]]) {
                cout << "no\n";
                exit(0);
            }
            visited[inp[i][j]] = true;
        }
    }

    for (int i = 0; i < n; ++i) {
        vector<bool> visited(n+1,false);
        for (int j = 0; j < k; ++j) {
            if (visited[inp[j][i]]) {
                cout << "no\n";
                exit(0);
            }
            visited[inp[j][i]] = true;
        }
    }

    for (int i = 0; i < n; ++i) {
        vector<vector<int>> adj_list(n+1); // cols -> allowed numbers
        for (int col = 1; col <=n; ++col) {
            if (inp[i][col-1] != 0) {
                adj_list[col].push_back(inp[i][col-1]);
            } else {
                vector<bool> allowed(n, true);
                for (int j = 0; j < i; ++j) {
                    allowed[inp[j][col-1]-1] = false;
                }
                for (int j = 0; j < n; ++j) {
                    if (allowed[j]) adj_list[col].push_back(j+1);
                }
            }
        }
        vector<int> matches(n+1);
        int mat = hopcroftkarp(adj_list, matches, n, n);
        if (mat != n) {
            cout << "no\n";
            exit(0);
        }
        for (int j = 1; j <= n; ++j) {
            inp[i][j-1] = matches[j];
        }
    }

    cout << "yes\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << inp[i][j] << " ";
        }
        cout << '\n';
    }

}