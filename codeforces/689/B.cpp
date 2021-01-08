#include <bits/stdc++.h>
using namespace std;

// COMPILER: GNU C++17	

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        int n, m;
        cin >>n >> m;

        bool arr[501][501] = {0};
        int dp[501][501] = {0};
        int count = 0;

        for (int j = 0; j < n; ++j) {
            string line;
            cin >> line;
            for (int k = 0; k < m; ++k) {
                arr[j][k] = line.at(k) == '*';
            }
        }

        for (int j = 0; j < m; ++j) {
            dp[0][j] = arr[0][j] ? 1 : 0;
            count += arr[0][j];
        }

        for (int j = 1; j < n; ++j) {
            for (int k = 0; k < m; ++k) {

                if (arr[j][k]) {

                    if (k == 0 || k == 1) {
                        dp[j][k] = 1;
                        count += dp[j][k];
                        continue;
                    }

                    dp[j][k] = 1 + min(min(dp[j][k-1], dp[j][k-2]), dp[j-1][k-1]);
                    count += dp[j][k];

                }

            }
        }

        cout << count << '\n';


    }
}   