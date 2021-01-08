#include <iostream>
using namespace std;

int round(int n) {
    return (n+5)/10*10;
}

int main() {
    int dp[2002][22] = {};
    int n, d;
    cin >> n >> d;
    int sumFromFront[2002];
    cin >> sumFromFront[1];
    dp[1][0] = round(sumFromFront[1]);
    for (int i = 2; i <= n; ++i) {
        cin >> sumFromFront[i];
        sumFromFront[i] += sumFromFront[i-1];
        dp[i][0] = round(sumFromFront[i]);
    }

    for (int N = 1; N <= n; ++N) {
        for (int D = 1; D <= d; ++D) {
            dp[N][D] = round(sumFromFront[N]);
            for (int i = 1; i < N; ++i) {
                int val = dp[i][D-1] + round(sumFromFront[N] - sumFromFront[i]);
                if (val < dp[N][D])
                    dp[N][D] = val;
            }
        }
    }
    cout << dp[n][d] << endl;
}