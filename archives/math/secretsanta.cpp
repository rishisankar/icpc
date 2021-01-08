#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

int main() {

    cout.setf(ios::fixed);
    cout.precision(8);

    vector<unsigned long long> factorial(20);
    factorial[0] = 1;
    for (int i = 1; i < 20; ++i) {
        factorial[i] = i * factorial[i-1];
    }

    const int N = 17;
    vector<ld> dp(N);

    dp[0] = 1;

    for (int i = 1; i < N; ++i) {
        ld prob = 1.0;
        for (int j = 0; j < i; ++j) {
            prob -= dp[j] / factorial[i-j];
        }
        dp[i] = prob;
    }

    int n;
    cin >> n;
    if (n >= 13) {
        n = 13;
    }
    cout << (1.0 - dp[n]) << '\n';

}