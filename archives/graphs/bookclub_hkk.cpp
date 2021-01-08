#include <bits/stdc++.h>
using namespace std;

// Hopcroft-Karp-Karzanov algorithm for maximum bipartite matching

// IMPORTANT: number vertices starting with 1, vertex 0 is reserved for use by algorithm

// main function: hopcroftkarp(adj_list, matches, L, R)
// adj_list (size L+1) should represent connected vertices in right set for each in set 1
// L = size of set 1, R = size of set 2
// matches (size L+1) will contain final match of each vertex in left set (or 0 if no match).

// source: https://www.geeksforgeeks.org/hopcroft-karp-algorithm-for-maximum-matching-set-2-implementation/


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

    int N, M;
    cin >> N >> M;

    vector<vector<int>> adj_list(N+1);
    for (int i = 0; i < M; ++i) {
        int a1,a2;
        cin >> a1 >> a2;
        ++a1; ++a2;
        adj_list[a1].push_back(a2);
    }

    vector<int> matches(N+1);
    int res = hopcroftkarp(adj_list, matches, N, N);

    if (res == N) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }


}