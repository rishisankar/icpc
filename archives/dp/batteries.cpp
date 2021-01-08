#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {

    vector<ll> dp(4712);
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i < 4712; ++i) {
        ll res = LLONG_MAX;
        for (ll j = 0; j < i; ++j) {
            res = min(res, 1 + max(j, dp[i-j-1]));
        }
        dp[i] = res;
    }

    while (true) {
        int n; cin >> n;
        if (n == 0) break;

        cout << dp[n-1] << '\n';
    }
        
}