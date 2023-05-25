#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>
#include <bits/extc++.h>
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

struct chash { // large odd number for C
	const uint64_t C = ll(4e18 * acos(0)) | 71;
	ll operator()(ll x) const { return __builtin_bswap64(x*C); }
};


const int X=250;
const int Y=6600;

ll three[66];
map<char,int> t;

// return vi(3^n) number of ways of ending at each mask on the last column
vector<int> magic(int n, int m, vector<string> g, int icpc)
{
  int N=three[m];
   vector<unordered_set<int>> v(X);
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
        if(9*last+cur==icpc)
        {
          ok=false;
          break;
        }
        last=cur;
      }
      if(ok) v[i].insert(j);
   }

   vector<__gnu_pbds::gp_hash_table<int,int,chash>> dp(N);
   rep(i,0,N)
   {
    int x=i;
    bool ok=true;
    int last=-1;
    rep(j,0,m)
    {
      last=x;
      if(g[0][j]!='?' && t[g[0][j]]!=x%3)
      {
        ok=false;
        break;
      }
      x/=3;
    }
    if(ok) dp[i][last%3]=1;
   }

  vector<__gnu_pbds::gp_hash_table<int,int,chash>> ndp(N);
   rep(k,1,n)
   {
    rep(i,0,N)
    {
      ndp[i].clear();
      int x=i;
      bool ok=true;
      int last=-1;
      rep(j,0,m)
      {
        last=x;
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
        trav(a,dp[mask])
        // rep(other_mask,0,three[n])
        if(a.F*3+last%3<three[n])
        (ndp[i][last%3+a.F*3]+=a.S)%=MOD;
      }
    }
    swap(dp,ndp);
   }

  vector<int> ans(Y,0);
  rep(i,0,N)
  trav(a,dp[i])
  // rep(j,0,three[n])
  (ans[a.F]+=a.S)%=MOD;

  return ans;
}

void solve() {
  int n,m;
  cin>>n>>m;

 
   vector<string> g(n);
   rep(i,0,n)
   cin>>g[i];

   int qs=0;
   rep(i,0,n) trav(a,g[i]) if(a=='?') qs++;

   if(n==1 || m==1)
   {
    cout<<three[qs]<<"\n";
    exit(0);
   }

   int mid=m/2;
   // [0 to mid] [mid to m] and then multiply

   vector<string> g1(n),g2(n);
   rep(i,0,n)
   g1[i]=g[i].substr(0,mid+1);


   
   rep(i,0,n)
   {
      g2[i]=g[i].substr(mid);
      reverse(all(g2[i]));
   }

  // dbg(g1,g2,mid);

  vector<int> ans1=magic(n,mid+1,g1,17);
  vector<int> ans2=magic(n,m-mid,g2,73);

  vector<ll> ans(Y,0);
  rep(i,0,three[n])
  ans[i]=(ans1[i]*(ll)ans2[i])%MOD;

  // dbg(ans1,ans2,ans);

  ll anss=accumulate(all(ans),0LL)%MOD;
  ll tot=three[qs];
  anss=(tot-anss+MOD)%MOD;

  cout<<anss<<"\n";


}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  three[0]=1;
  rep(i,1,66)
  three[i]=(3*(three[i-1]))%MOD;

  t['I']=0;
  t['P']=1;
  t['C']=2;

  solve();
}