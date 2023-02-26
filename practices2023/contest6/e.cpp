#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i  < (b); i++)
#define F first
#define S second
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v)
{
  os << '{'; string sep; for(const auto &x: v) os << sep << x, sep = ", "; return os << '}'; 
}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ")";
}

void dbg_out() { cerr << endl; }

template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...);}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif


const int MOD = 1e9+7;
const int MAXN = 300, MAXS=300+5;
int N, S;
vi dp[MAXN][2];
int visited[MAXN];
int sk[MAXN], pk[MAXN];
vi adj[MAXN];

void sol(int cur, int prev)
{
  if(visited[cur]) {
    return;
  }
  visited[cur] = true;
  if(prev != -1 && adj[cur].size() == 1) {
    // leaf
    if(sk[cur] > S) return;
    dp[cur][1][sk[cur]] = pk[cur];
    return;
  }
  for(int x: adj[cur]) {
    if(x == prev) continue;
    sol(x, cur);
    rep(use, 0, 2) {
      for(int i = S; i >= 0; i--) {
        for(int j = i; j >= 1; j--) {
          dp[cur][use][i] = max(dp[cur][use][i], dp[cur][use][i-j] + dp[x][1-use][j]);
        }
      }
    }
  }
  int use = 1;
  for(int i = S; i >= sk[cur]; i--) {
    dp[cur][use][i] = max(dp[cur][use][i-sk[cur]] + pk[cur], dp[cur][use][i]);
  }
  rep(i, 0, S+1) {
    dp[cur][use][i] = max(dp[cur][use][i], dp[cur][1-use][i]);
  }

  dbg(cur, prev, dp[cur][0]);
  dbg(cur, prev, dp[cur][1]);
}

void solve()
{
  cin >> N >> S;
  rep(i, 0, N) {
    dp[i][0].resize(S+1);
    dp[i][1].resize(S+1);
    dp[i][0].assign(S+1, 0);
    dp[i][1].assign(S+1, 0);
  }
  rep(i, 0, N) {
    cin >> sk[i] >> pk[i];
  }
  int a, b;
  rep(i, 0,N-1) {
    cin >> a >> b;
    a--, b--;
    adj[a].pb(b); adj[b].pb(a);
  }
  sol(0, -1);
  int ans = 0;
  rep(i, 0, S+1) {
    ans = max(ans, dp[0][1][i]);
  }
  cout << ans << endl;
}

int main()
{
  solve();
}