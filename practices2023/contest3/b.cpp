#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i <(b); i++)
#define trav(a, x) for (auto& a: x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define F first
#define S second
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) 
{ os << '{'; string sep; for (const auto &x: v) os << sep << x, sep = ", "; return os << '}';}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) 
{ return os << '(' << p.first << ", " << p.second << ')'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
const int MOD = 1e9+7;

void solve() {
  int h,w; cin >> h >> w;
  vector<vector<ll>> dp(h+1, vector<ll>(w+1, 0));
  dp[1][1] = 1;
  for (int i = 2; i <= h; ++i) {
    for (int j = 0; j <= w; ++j) {
      if (j < i) {
        // impossible to get height i
        dp[i][j] = dp[i-1][j];
      } else {
        for (int wl = 1; wl < j; ++wl) {
          dp[i][j] += (dp[i-1][wl]*dp[i][j-wl]) % MOD;
          dp[i][j] %= MOD;
        }
      }
    }
  }
  ll ans = (dp[h][w] + MOD - dp[h-1][w]) % MOD;

  dbg(dp);

  cout << ans << '\n';

}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  solve();
}