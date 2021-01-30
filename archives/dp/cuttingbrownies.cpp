// doesn't work!!

#include <bits/stdc++.h>
using namespace std;

int S(int n, int m, vector<vector<int>>& memo) {

    if (memo[n][m] != INT_MAX) {
        return memo[n][m];
    }

    if (m == 1) {
        return memo[n][m] = n-1;
    } 

    for (int k = 1; k < m; ++k) {
        memo[n][m] = min(memo[n][m], -S(k,n,memo)-S(m-k,n,memo));
    }

    return memo[n][m];

}

int main() {

    int N; cin >> N;

    for (int tests = 0; tests < N; ++tests) {

        int m, n;
        cin >> m >> n;
        string person; cin >> person;
        if (person == "Harry") {
            int tmp = n;
            n = m;
            m = tmp;
        }
        int bound = max(n,m) + 1;
        vector<vector<int>> memo(bound, vector<int>(bound, INT_MAX));

        cout << person;
        if (S(n, m, memo) >= 0) {
            cout << " cannot win\n";
        } else {
            cout << " can win\n";
        }

    }

}