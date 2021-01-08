#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {

    ll M = 1000000007;

    int N; cin >> N;
    string word; cin >> word;
    unordered_map<string, ll> m;

    for (int i = 0; i < N; ++i) {
        string sub;
        ll val;
        cin >> sub >> val;
        m[sub] = val;
    }

    N = word.size();

    // # of meanings
    vector<ll> dp(word.size(), 0);

    // current total length (specifies last index)
    for (int i = 0; i < N; ++i) {
        string curword = word.substr(0, i+1);
        auto tmp_it =m.find(curword);
        if (tmp_it != m.end()) {
            dp[i] += tmp_it->second;
        }
        dp[i] %= M;
        for (int j = 0; j < i; ++j) {
            string right = word.substr(j+1,i-j);
            auto it = m.find(right);
            if (it != m.end()) {
                dp[i] += dp[j] * it->second;
                dp[i] %= M;
            }
        }
    }

    cout << dp[word.size() - 1] << '\n';

}