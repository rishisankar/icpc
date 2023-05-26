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
    cout<<w+b<<"\n";
    return;
  }

  ll g=__gcd(w,b);
  w/=g;
  b/=g;
  pii r={w,b};
  // cerr<<w<<b<<"\n";
  stack<pii> s;
  rep(i,0,n) s.push(v[n-i-1]);
  ll ans=0;
  ll cw=0,cb=0;
  int k=0;
  while(!s.empty())
  {
    // k++;
    // if(k>=10) exit(0);
    pii x=s.top();
    s.pop();
    pii nx={cw,cb};
    cerr<<cw<<" "<<cb<<"\n";
    cerr<<x.F<<" "<<x.S<<"\n";

    if(x.S) // b
    { 
      nx.S+=x.F;
      if(cw==0)
      {
        cw=nx.F;
        cb=nx.S;
        continue;
      }
      if(nx.F*r.S <= r.F*nx.S && cw*r.S >= r.F*cb)
      {
        ll take=(cw*r.S)/r.F-cb;
        assert(take<=x.F);
        x.F-=take;
        ans++;
        if(x.F>0) s.push(x);
        cw=0;
        cb=0;
      }
      else
      {
        cw=nx.F;
        cb=nx.S;
      }
    }
    else
    {
      nx.F+=x.F;
      if(cb==0)
      {
        cw=nx.F;
        cb=nx.S;
        continue;
      }
      if(nx.F*r.S >= r.F*nx.S && cw*r.S <= r.F*cb)
      {
        ll take=(cb*r.F)/r.S-cw;
        assert(take<=x.F);
        x.F-=take;
        ans++;
        if(x.F>0) s.push(x);
        cw=0;
        cb=0;
      }
      else
      {
        cw=nx.F;
        cb=nx.S;
      }
    }

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