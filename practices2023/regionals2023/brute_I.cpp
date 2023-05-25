#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <(b); ++i)
#define trav(a,x) for(auto& a:x)
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

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) {
  return os<< '(' << p.first << ", " << p.second << ')';
}
template<typename T> ostream & operator<<(ostream &os, const vector<T> &v) {
  os << '{';
  string sep;
  for(const auto &x: v) os << sep << x, sep = ", ";
  return os << '}';
}

void dbg_out() {cerr << endl;}
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) {
  cerr << ' ' << H; dbg_out(T...);
}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

const ll MOD = 998244353;

ll three[66];

void solve() {
  int n,m;
  cin>>n>>m;

  map<char,int> t;
  t['I']=0;
  t['P']=1;
  t['C']=2;
   vector<string> g(n);
   rep(i,0,n)
   cin>>g[i];

   int qs=0;
   rep(i,0,n) trav(a,g[i]) if(a=='?') qs++;


  int N=three[m];
   vector<unordered_set<int>> v(N);
   rep(i,0,N)
   rep(j,0,N)
   {
      int x=i,y=j;
      bool ok=true;
      int cur;
      int last=3*(x%3)+(y%3);
      rep(k,0,m-1)
      {
        x/=3;
        y/=3;
        cur=3*(x%3)+(y%3);
        if(9*last+cur==17)
        {
          ok=false;
          break;
        }
        last=cur;
      }
      if(ok) v[i].insert(j);
   }

   vector<ll> dp(N,0);
   rep(i,0,N)
   {
    int x=i;
    bool ok=true;
    rep(j,0,m)
    {
      if(g[0][j]!='?' && t[g[0][j]]!=x%3)
      {
        ok=false;
        break;
      }
      x/=3;
    }
    if(ok) dp[i]=1;
   }

   rep(k,1,n)
   {
    vector<ll> ndp(N,0);
    rep(i,0,N)
    {
      int x=i;
      bool ok=true;
      rep(j,0,m)
      {
        if(g[k][j]!='?' && t[g[k][j]]!=x%3)
        {
          ok=false;
          break;
        }
        x/=3;
      }
      if(ok)
      {
        rep(mask,0,N)
        if(v[mask].find(i)!=v[mask].end())
        (ndp[i]+=dp[mask])%=MOD;
      }
    }
    dp=ndp;
   }

  ll ans=accumulate(all(dp),0LL)%MOD;
  ll tot=three[qs];
  ans=(tot-ans+MOD)%MOD;

  cout<<ans<<"\n";


}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  three[0]=1;
  rep(i,1,66)
  three[i]=(3*(three[i-1]))%MOD;
  solve();
}