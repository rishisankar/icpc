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


ll s;

bool check(double r) {
  ll cnt = 0;
  rep(i, 1, r) {
    cnt += sqrt(r*r-i*i);
  }
  //cerr << r << ' ' << cnt << endl;
  return 4*cnt > s;
}

void solve() {
  cin >> s;
  double lo = 0;
  double hi = 1e6;
  while(hi-lo > 1e-7) {
    double m = (hi+lo)/2;
    if(check(m)) hi = m;
    else lo = m;
  }
  cout << fixed << setprecision(9) << hi << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}