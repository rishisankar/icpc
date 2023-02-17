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
#define int long long

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
const ll MOD = 1e9+7;
int n;

int solve(int mask, vi &dp, map<int,vector<pair<int,int>>> &proofs)
{
  if(dp[mask]!=-1) return dp[mask];

  rep(i,0,n)
  {
    if(mask&(1<<i))
    {
      int have_mask=mask^(1<<i);
      trav(a,proofs[i])
      {
        dbg(have_mask,a.S);
        if(((have_mask|(a.S)))==have_mask) // have all deps
        {
          if(dp[mask]==-1) dp[mask]=a.F+solve(have_mask,dp,proofs);
          else dp[mask]=min(dp[mask],a.F+solve(have_mask,dp,proofs));
        }
      }
    }
  }
  
  if(dp[mask]==-1) dp[mask]=MOD;
  return dp[mask];
}

void solve() {
  cin>>n;

  map<int,vector<pair<int,int>>> proofs;
  rep(i,0,n)
  {
    int p;
    cin>>p;
    rep(j,0,p)
    {
      int l;
      cin>>l;
      int d;
      cin>>d;
      vi deps(d);
      rep(k,0,d)
      cin>>deps[k];
      int mask=0;
      trav(a,deps)
      mask+=(1<<a);
      proofs[i].pb({l,mask});
    }
  }

  rep(i,0,n)
  dbg(proofs[i]);

  vi dp(1<<n,-1);
  dp[0]=0;

  int ans=MOD;
  rep(i,0,(1<<n))
  {
    if(i%2)
    ans=min(ans,solve(i,dp,proofs));
  }

  cout<<ans<<endl;
  dbg(dp);

}

int32_t main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  solve();
}