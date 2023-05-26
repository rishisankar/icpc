#include <bits/stdc++.h>

using namespace std;
#define rep(i,a,b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto &x)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define F first
#define S second
#define pb push_back
#define mp make_pair
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;

void solve()
{
  int n; cin >> n;
  vector<pair<pii,int>> v;
  rep(i,0,n) {
    int a,b,c; cin >> a >> b >> c;
    v.pb({{a,b},c});
  }
  sort(all(v), [&](auto& p1, auto& p2) {
    return p1.F.S < p2.F.S || (p1.F.S == p2.F.S && p1.F.F < p2.F.F) || (p1.F == p2.F && p1.S < p2.S);
  });
  vector<ll> dp(n, LLONG_MAX);
  for (int a = 0; a < n; ++a) {
    rep(p, -1, a) {
      ll pv = (p == -1 ? 0 : dp[p]);
      int ls = INT_MAX, ee = -1, mx = 0;
      rep(i, p+1, a+1) {
        ls = min(ls, v[i].F.F);
        ee = max(ee, v[i].F.S);
        mx = max(mx, v[i].S);
      }
      rep(kp, p+1, a+1) {
        int k = v[kp].F.S;
        if (k < ls || k > ee) continue;
        dp[a] = min(dp[a], pv + mx);
      }
    }
  }
  cout << dp[n-1] << '\n';

}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t ; cin >> t;
  for (int i = 0; i < t; ++i)
  solve();
}