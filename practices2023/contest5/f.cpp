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
  int N;
  cin >> N;
  int costs[N];
  rep(i, 0, N) {
    cin >> costs[i];
  }
  int dp[N+1][3];
  const int INF = 1e9;
  dp[0][0] = 0; dp[0][1] = 0; dp[0][2] = -INF;
  rep(d, 0, N) {
    dp[d+1][2] = max(dp[d][2], dp[d][0] - costs[d]);
    dp[d+1][1] = dp[d][2] + costs[d];
    dp[d+1][0] = max(dp[d][1], dp[d][0]);
  }
  cout << max(max(dp[N][0], dp[N][1]), dp[N][2]) << endl;
}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  solve();
}