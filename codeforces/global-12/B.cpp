#include <bits/stdc++.h>
using namespace std;

// COMPILER: GNU C++17	

bool thresh(int x1, int y1, int x2, int y2, int K) {
    int dist = abs(x2 - x1) + abs(y2 - y1);
    return (dist <= K);
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        int n, K;
        cin >>n >> K;

        int lookup[102][2];

        vector<int> adj[102];
        for (int j = 0; j < n; ++j) {
            cin >> lookup[j][0] >> lookup[j][1];
            for (int k = 0; k < j; ++k) {
                if (thresh(lookup[j][0], lookup[j][1], lookup[k][0], lookup[k][1], K)) {
                    adj[j].push_back(k);
                    adj[k].push_back(j);
                }
            }
        }
        bool found = false;
        for (int j = 0; j < n; ++j) {
            if (adj[j].size() == n-1) {
                cout << 1 << '\n';
                found = true;
                break;
            }
        }
        if (!found) {
            cout << -1 << '\n';
        }
    }
}   