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
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double ld;

void solve() {
  ll n,t; cin >> n >> t;
  ld lo = 0, hi = 1e18;
  vector<pair<pii,ll>> v(n);
  rep(i,0,n) {
    cin >> v[i].F.F >> v[i].F.S >> v[i].S;
  }
  rep(Q,0,200) {
    ld k = lo+(hi-lo)/2;
    ld z = 0;
    rep(i,0,n) {
      ld c = k * v[i].S;
      c = min(c, (ld)v[i].F.S);
      c = max(c, (ld)v[i].F.F);
      z += c;
    }
    if (z > t) hi = k;
    else lo = k;
  }
  ld k = lo;
  rep(i,0,n) {
    ld c = k * v[i].S;
    c = min(c, (ld)v[i].F.S);
    c = max(c, (ld)v[i].F.F);
    cout << setprecision(30) << c << '\n';
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}