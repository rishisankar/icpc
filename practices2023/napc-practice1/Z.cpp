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
typedef pair<long long, long long> pii;
typedef vector<long long> vi;

void solve()
{
  int n;
  cin>>n;
  vector<pii> v(n);
  ll w=0,b=0;
  rep(i,0,n)
  {
    ll x;
    cin>>x;
    char ch;
    cin>>ch;
    if(ch=='W') {v[i]={x,0};w+=x;}
    else {v[i]={x,1};b+=x;}
  }

  // rep(i,0,n)
  // cerr<<v[i].F<<" "<<v[i].S<<"\n"; 

  if(w==0 || b==0)
  {
    cout<<(w+b)<<"\n";
    return;
  }

  ll g=__gcd(w,b);
  w/=g;
  b/=g;
  pii r={w,b};
  ll cw=0,cb=0;
  ll ans=0;
  rep(i,0,n)
  {
    ll ncw=cw;
    ll ncb=cb;
    if(v[i].S)
    {
      ncb+=v[i].F;
    }
    else
    {
      ncw+=v[i].F;
    }
    if(ncw==0 || ncb==0)
    {
      cw=ncw;
      cb=ncb;
      continue;
    }
    if(cw*r.S>=cb*r.F && ncw*r.S<=ncb*r.F) ans++;
    if(cw*r.S<=cb*r.F && ncw*r.S>=ncb*r.F) ans++;
    cw=ncw;
    cb=ncb;
    
  }


  cout<<ans<<"\n";
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin>>t;
  rep(i,0,t)
  solve();
}