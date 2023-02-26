#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i <(b); i++)
#define trav(a, x) for(auto &a: x)
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

template<typename T> ostream& operator << (ostream &os, const vector<T> &v) { os << '{'; string sep; for(const auto &x: v) os << sep << x, sep = ", "; return os << '}';}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...);}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

const ll MOD = 1e9+7;

ll dfs(ll n, ll m, ll k, int d)
{
  dbg(n,m,k,d);
  if(d>4) return MOD;
  if(k==n*m || k==0) return 0;
  if((k%n==0) || (k%m==0)) return 1;
  if((k<n) || (k<m)) return 2;

  ll ans=MOD;
  ans=min(ans,1+dfs(n-k/m,m,k%m,d+1));
  ans=min(ans,1+dfs(n,m-k/n,k%n,d+1));
  if(k/m+1<n)
  ans=min(ans,1+dfs(k/m+1,m,k,d+1));
  if(k/n+1<m)
  ans=min(ans,1+dfs(n,k/n+1,k,d+1));
  return ans;
}

void solve()
{
  ll n,m,a;
  cin>>n>>m>>a;

  cout<<dfs(n,m,a,0)<<endl;
}

int main()
{

  solve(); 
}