#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;

int main() {

    vector<ll> res(15);
    vector<vector<vector<ll>>> dp(50, vector<vector<ll>>(50, vector<ll>(2, 0)));

    dp[25][25][0] = 1;

    for (int k = 1; k <= 14; ++k) {
        for (int i = 0; i < 50; ++i) {
            for (int j = 0; j < 50; ++j) {
                dp[i][j][k%2] = 0;
            }
        }

        for (int i = 0; i < 50; ++i) {
            for (int j = 0; j < 50; ++j) {
                if (dp[i][j][(k+1)%2]) {
                    ll tmp = dp[i][j][(k+1)%2];
                    int km = k % 2;

                    if (j%2 == 0) {
                        dp[i+1][j][km] += tmp;
                        dp[i-1][j][km] += tmp;
                        dp[i][j+1][km] += tmp;
                        dp[i][j-1][km] += tmp;
                        dp[i+1][j+1][km] += tmp;
                        dp[i+1][j-1][km] += tmp;
                    } else {
                        dp[i+1][j][km] += tmp;
                        dp[i-1][j][km] += tmp;
                        dp[i-1][j+1][km] += tmp;
                        dp[i-1][j-1][km] += tmp;
                        dp[i][j+1][km] += tmp;
                        dp[i][j-1][km] += tmp;
                    }
                }
            }
        }

        res[k] = dp[25][25][k%2];
    }

    int t;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        int n; cin >> n;
        cout << res[n] << '\n';
    }



}