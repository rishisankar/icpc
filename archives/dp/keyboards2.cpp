#include <bits/stdc++.h>
using namespace std;

// (cleaner) soln to keyboardconcert

int main() {

    int n, m;
    cin >> n >> m;

    // n x 1000 bitmap (which notes each of the n instruments can play)
    vector<vector<bool>> vec(n, vector<bool>(1001, false));

    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int tmp;
            cin >> tmp;
            vec[i][tmp] = true;
        }
    }

    vector<int> notes(m);
    for (int i = 0; i < m; ++i) {
        cin >> notes[i];
    }

    if (m == 1) {
        cout << 0 << '\n';
        return 0;
    }

    // m x n table (after each note, minimum # of switches to play m notes ending on nth instrument)
    vector<vector<int>> dp(m, vector<int>(n, 0));

    // base case
    for (int i = 0; i < n; ++i) {
        dp[0][i] = vec[i][notes[0]] ? 0 : 1;
    }

    int minimum;
    for (int i = 1; i < m; ++i) {
        minimum = INT_MAX;
        for (int j = 0; j < n; ++j) {
            if (vec[j][notes[i]]) {
                dp[i][j] = dp[i-1][j];
                minimum = min(minimum, dp[i][j]);
            }
        }
        for (int j = 0; j < n; ++j) {
            if (!vec[j][notes[i]]) {
                dp[i][j] = minimum + 1;
            }
        }
    }

    cout << minimum << '\n';

}