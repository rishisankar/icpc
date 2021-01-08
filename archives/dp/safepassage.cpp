#include <bits/stdc++.h>
using namespace std;

int countBits(int i) {
    int count = 0;
    while (i != 0) {
        count += (i & 1);
        i >>= 1;
    }
    return count;
}

int main() {
    int N;
    cin >> N;
    vector<int> times(N);
    for (int i = 0; i < N; ++i) {
        cin >> times[i];
    }

    int len = 1 << N;

    // ith bit represents ith person is on gate (0) or dorm (1)
    // 0 = cloak at gate, 1 = cloak at dorm
    vector<vector<int>> dp(len, vector<int>(2, INT_MAX));

    vector<vector<int>> nums(N+1);
    for (int i = 0; i < len; ++i) {
        nums[countBits(i)].push_back(i);
    }

    dp[0][0] = 0;

    for (int i = 2; i <= N; ++i) {

        for (int n : nums[i-2]) {
            for (int a = 0; a < N; ++a) {
                for (int b = 0; b < N; ++b) {
                    if (a == b) continue;
                    if ((n >> a) & 1 == 1) continue;
                    if ((n >> b) & 1 == 1) continue;
                    int tmp = n + (1 << a) + (1 << b);
                    dp[tmp][1] = min(dp[tmp][1], dp[n][0] + max(times[a],times[b]));
                }
            }
        }

        for (int n : nums[i]) {
            for (int a = 0; a < N; ++a) {
                int tmp2 = (n >> a) & 1;
                if (tmp2 == 0) continue;
                int tmp = n - (1 << a);
                dp[tmp][0] = min(dp[tmp][0], dp[n][1] + times[a]);
            }
        }

    }

    cout << dp[len-1][1] << '\n';
}