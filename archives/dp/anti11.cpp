#include <iostream>
#include <vector>
using namespace std;

int main() {
    int T;
    int mod = 1000000007;
    cin >> T;

    int max = 0;
    vector<int> inputs;
    for (int i = 0; i < T; ++i) {
        int n;
        cin >> n;
        if (max < n) max = n;
        inputs.push_back(n);
    }

    int dp[10001][2];
    dp[0][0] = 0;
    dp[0][1] = 0;
    dp[1][0] = 1;
    dp[1][1] = 1;
    for (int i = 2; i <= max; ++i) {
        dp[i][0] = (dp[i-1][0] + dp[i-1][1]) % mod;
        dp[i][1] = dp[i-1][0];
    }

    for (int i : inputs) {
        cout << (dp[i][0] + dp[i][1]) % mod << endl;
    }
}