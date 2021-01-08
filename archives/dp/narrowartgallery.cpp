#include <iostream>
using namespace std;

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int N, k, l, r;
    cin >> N >> k;

    int dp[201][201][3]; // N by k by 3
    // for the 3rd dim: index 0 is both of prev open, 1 is left open, 2 is right open

    for (int i = 0; i < 201; ++i) {
        for (int j = 0; j < 201; ++j) {
            for (int k = 0; k < 3; ++k) {
                dp[i][j][k] = -1;
            }
        }
    }

    cin >> l >> r;
    dp[0][0][0] = l + r;

    dp[0][1][1] = l;
    dp[0][1][2] = r;

    for (int i = 1; i <= N; ++i) {
        cin >> l >> r;
        dp[i][0][0] = dp[i-1][0][0] + l + r;
        for (int j = 1; j <= k && j <= i + 1; ++j) {
            dp[i][j][0] = max(max(dp[i-1][j][0], dp[i-1][j][1]), dp[i-1][j][2]);
            if (dp[i][j][0] != -1) dp[i][j][0] += l + r;
            dp[i][j][1] = max(dp[i-1][j-1][0], dp[i-1][j-1][1]);
            if (dp[i][j][1] != -1) dp[i][j][1] += l;
            dp[i][j][2] = max(dp[i-1][j-1][0], dp[i-1][j-1][2]);
            if (dp[i][j][2] != -1) dp[i][j][2] += r;
        }
    }

    cout << dp[N][k][0] << endl;
}