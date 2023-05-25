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

const int MOD = 1e9+7;

void solve() {
  int s, t, n;
  cin >> s >> t >> n;
  vector<pii> saws(n);
  int m, h;
  rep(i, 0, n) {
      cin >> m >> h;
      saws[i] = {h,m};
  }
  sort(all(saws));
  int start;
  for(start = 0; start < n; start++) {
    if(saws[start].S >= s) break;
  }
  if(start == n) {
    cout << "-1\n";
    return;
  }
  double cur = s;
  int next = start-1;
  double ans = 0;
  while(next >= 0) {
    if(saws[next].S < saws[start].S) {
      int d = max(saws[next].S, t);
      ans += log2(cur/d)*saws[start].F;
      start = next;
      next = start-1;
      cur = d;
      if(d == t) {
        cout << fixed << setprecision(30) << ans << '\n';
        return;
      }
    } else {
      next--;
    }
  }
  ans += log2(cur/t)*saws[start].F;
  cout << fixed << setprecision(30) << ans << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}