#include <iostream>
using namespace std;

int main() {
    int dp[101][101];
    dp[2][0] = 1;
    dp[2][1] = 1;
    for (int n = 3; n <= 100; ++n) {
        dp[n][0] = 1;
        dp[n][n-1] = 1;
        for (int v = 1; v < n-1; ++v) {
            dp[n][v] = (dp[n-1][v] * (v+1) + dp[n-1][v-1] * (n-v)) % 1001113;
        }
    }
    int P, K, N, v;
    cin >> P;
    for (int i = 0; i < P; ++i) {
        cin >> K >> N >> v;
        cout << K << " " << dp[N][v] << endl;
    }
}