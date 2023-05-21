#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <(b); i++)
#define trav(a,x) for(auto& a:x)
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
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) {
  return os <<'(' <<p.F << ", " << p.S << ')';
}
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) {
  os << '{';
  string sep;
  for(const auto &x: v) os << sep << x, sep = ", ";
  return os << '}';
}

void dbg_out() {cerr << endl;}
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) {
  cerr << ' ' << H; dbg_out(T...);
}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
const int MOD = 1e9+7;

ll n,p,q,s;
ll INF=1e15;

int magic(ll d, vector<ll> v, multiset<ll> w)
{
  ll tot=0;
  rep(i,0,p)
  {
    if(sz(w)==0) continue;
    ll x=v[i];
    auto it=w.upper_bound(min(s-x,x+d));
    if(it==w.begin()) continue;
    --it;
    ll y=*it;
    if(y<x-d) continue;
    tot++;
    w.erase(w.find(y));
  }
  return (tot>=n);
}


void solve() {
  
  cin>>n>>p>>q>>s;
  vector<ll> v;
  multiset<ll> w;
  rep(i,0,p)
  {
    ll x;
    cin>>x;
    v.pb(x);
  }
  sort(all(v));
  reverse(all(v));
  rep(i,0,q)
  {
    ll x;
    cin>>x;
    w.insert(x);
  }

  ll l=0,r=1e12;

  ll ans=INF;
  while(l<=r)
  {
    ll mid=(l+r)/2;
    if(magic(mid,v,w))
    {
      ans=min(ans,mid);
      r=mid-1;
    }
    else
    {
      l=mid+1;
    }
  }

  if(ans==INF) ans=-1;
  cout<<ans<<"\n";  
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}