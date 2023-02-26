#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {

  int n;
  cin>>n;
  vector<ll> v(n);
  for(int i = 0; i < n; ++i) {
    cin >> v[i];
  }
  vector<vector<ll>> dp(n, vector<ll>(n+1, LLONG_MIN));
  // dp[i][j] = max score possible starting on square i with jump dist j

  // base
  for (int i = 0; i < n+1; ++i) {
    dp[n-1][i] = v[n-1];
  }

  for (int i = n-2; i >= 0; --i) {
    ll best = dp[i+1][1];
    for (int j = 1; j <= n; ++j) {
      int nj = i + j;
      if (nj < n) {
        best = max(best, dp[nj][j]);
      }
      dp[i][j] = best + v[i];
    }
  }

  cout << dp[0][n] << '\n';


}