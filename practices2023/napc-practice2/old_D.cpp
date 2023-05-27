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
  map<int,vi> x_blocks;
  map<int,vi> y_blocks;
  string path;
  cin>>path;

  int n=sz(path);
  pii cur={0,0};
  rep(i,0,n)
  {
    ll sc=(1<<(i+1));
    pii dir=m[path[i]];
    dir.F*=sc;
    dir.S*=sc;
    if(path[i]=='D')
    {
      ll ny=cur.S+dir.S:
      // find first thing that is above ny, and make sure it is higher that cur.S
      int idx=lower_bound(all(x_blocks[cur.F]),ny)-x_blocks[cur.F].begin();
      if(idx==sz(x_blocks[cur.F]) || x_blocks[cur.F][idx]>cur.S) // found nothing
      {
        // add a block
        x_blocks[cur.F].pb()
      }
      else
      {

      }
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