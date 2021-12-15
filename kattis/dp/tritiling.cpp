#include <bits/stdc++.h>
using namespace std;

int main() {

    int dp[31];

    dp[0] = 1;
    dp[1] = 2;
    dp[2] = 3;

    for (int i = 3; i <= 30; ++i) {
        if (i % 2 == 0) {
            dp[i] = 3 * dp[i-2] + dp[i-3];
        } else {
            dp[i] = 2 * dp[i-1] + dp[i-2];
        }
    }

    int n;
    while (true) {
        cin >> n;
        if (n == -1) break;
        if (n % 2 == 0) cout << dp[n] << '\n';
        else cout << 0 << '\n';
    }

}