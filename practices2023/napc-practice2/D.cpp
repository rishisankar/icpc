#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<(b) ; ++i)
#define trav(a,x) for(auto &a:x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define F first
#define S second
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef pair<long long, long long> pii;
typedef vector<long long> vi;

map<char,pii> m;

void solve() {
  set<pii> seen;
  set<pii> blocks;
  string path;
  cin>>path;

  int n=sz(path);
  pii cur={0,0};
  bool any_new;
  pii np;
  rep(i,0,n)
  {
    ll sc=(1<<(i+1));
    pii dir=m[path[i]];
    any_new=false;
    rep(i,0,sc)
    {
      ll nx=cur.F+dir.F;
      ll ny=cur.S+dir.S;
      if(blocks.count(mp(nx,ny))) break;
      if(seen.insert(mp(nx,ny)).S) any_new=true,np=mp(nx,ny);
      cur.F=nx;
      cur.S=ny;
    }
    ll nx=cur.F+dir.F;
    ll ny=cur.S+dir.S;
    blocks.insert(mp(nx,ny));
  }

  if(!any_new)
  {
    cout<<"impossible"<<"\n";
    return;
  }
  else
  {
    //  cout<<"possible"<<"\n";
    // return;
    cout<<-np.F<<" "<<-np.S<<"\n";
    cout<<sz(blocks)<<"\n";
    trav(a,blocks)
    {
      cout<<a.F-np.F<<" "<<a.S-np.S<<"\n";
    }
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  m['D']={0,-1};
  m['U']={0,1};
  m['L']={-1,0};
  m['R']={1,0};
  solve();
}