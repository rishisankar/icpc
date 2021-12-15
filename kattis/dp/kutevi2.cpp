#include <bits/stdc++.h>
using namespace std;

int main() {

    int n, k;
    cin >> n >> k;

    vector<bool> dp(360, false);

    vector<int> initial(n);
    for (int i = 0; i < n; ++i) {
        cin >> initial[i];
        dp[initial[i]] = true;
    }

    bool worked = true;
    while (worked) {
        worked = false;
        for (int i = 0; i < 360; ++i) {
            if (dp[i]) continue;
            for (int j = 0; j < n; ++j) {
                if (dp[(360+i-initial[j])%360]) {
                    dp[i] = true;
                    worked = true;
                    continue;
                }
            }
        }
    }

    for (int i = 0; i < k; ++i) {
        int test;
        cin >> test;
        if (dp[test]) cout << "YES\n"; else cout << "NO\n";
    }

}