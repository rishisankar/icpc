#include <bits/stdc++.h>
using namespace std;

struct st {
    int pt;
    long long weight;
    st() {}
    st(int _pt, long long _weight) : pt(_pt), weight(_weight) {}
};

long long numPaths(int pt, vector<vector<int>>& path_list, vector<long long>& memo) {
    if (memo[pt] != -1) {
        return memo[pt];
    }

    long long count = 0;
    for (int adj : path_list[pt]) {
        count += numPaths(adj, path_list, memo);
    }
    return memo[pt] = count;
}

int main() {

    int N, M;

    while (true) {
        cin >> N;
        if (N == 0) break;
        cin >> M;

        vector<vector<st>> adj_list(N+1);
        for (int i = 0; i < M; ++i) {
            int v1, v2;
            long long weight;
            cin >> v1 >> v2 >> weight;
            st s1(v1, weight);
            st s2(v2, weight);
            adj_list[v1].push_back(s2);
            adj_list[v2].push_back(s1);
        }

        // Dijkstra (path length to pt 2)
        vector<long long> dists(N+1, LLONG_MAX);
        vector<long long> shortest(N+1, -1);
        dists[2] = 0;
        while(true) {
            int minpt = 0;
            for (int i = 1; i <= N; ++i) {
                if (shortest[i] == -1 && dists[i] <= dists[minpt]) {
                    minpt = i;
                }
            }
            if (minpt == 0) break;
            shortest[minpt] = dists[minpt];
            for (st edge : adj_list[minpt]) {
                if (shortest[edge.pt] == -1) {
                    dists[edge.pt] = min(dists[edge.pt], edge.weight + dists[minpt]);
                }
            }
        }

        vector<vector<int>> path_list(N+1);
        for (int i = 1; i <= N; ++i) {
            for (st edge : adj_list[i]) {
                if (shortest[edge.pt] < shortest[i]) {
                    path_list[i].push_back(edge.pt);
                }
            }
        }

        vector<long long> memo(N+1, -1);
        memo[2] = 1;

        cout << numPaths(1, path_list, memo) << '\n';

    }


}