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

#define int __int128_t

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;

int multinomial(vi& v) {
  int c = 1, m = v.empty() ? 1 : v[0];
  rep(i,1,sz(v)) rep(j,0,v[i])
  c = c* ++m/(j+1);
  return c;
}

#undef int

set<ll> ans;
ll D, H;
void parts(vi &p, ll sum, ll big) {
  if(sz(p) == D) {
    if(sum == H-1) {
      ans.insert(multinomial(p));
    }
    return;
  }
  ll n = (H-sum)/(D-sz(p));
  rep(i, big, n+1) {
    p.pb(i);
    parts(p, sum+i, i);
    p.pop_back();
  }
}

void solve() {
  cin >> D >> H;
  vi x;
  parts(x, 0, 0);
  for(ll x: ans) {
    cout << x << '\n';
  }
}

int32_t main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}