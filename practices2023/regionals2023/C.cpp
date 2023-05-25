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

struct Tree {
  typedef ll T;
  static constexpr T unit = 0;
  T f(T a, T b) { return a + b; }
  vector<T> s; int n;
  Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
  void update(int pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(int b, int e) {
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

typedef pair<ll,ll> pll;

void solve() {
  int n; ll X; cin >> n >> X;
  vector<pair<pll, pll>> pts(n);
  rep(i,0,n) {
    cin >> pts[i].F.F >> pts[i].F.S >> pts[i].S.F;
    pts[i].S.S = i;
  }
  sort(all(pts), [&](auto& p1, auto& p2) {
    pll s1 = p1.F; if (s1.S<0) { s1.F*=-1; s1.S*=-1; }
    pll s2 = p2.F; if (s2.S<0) { s2.F*=-1; s2.S*=-1; }
    return s1.F*s2.S < s1.S*s2.F;
  });
  dbg(pts);
  vector<ll> ans(n);
  vi p(n); iota(all(p), 0);
  sort(all(p), [&](int x, int y) {
    pll s1 = pts[x].F; s1.F -= X; if (s1.S<0) { s1.F*=-1; s1.S*=-1; }
    pll s2 = pts[y].F; s2.F -= X; if (s2.S<0) { s2.F*=-1; s2.S*=-1; }
    return s1.F*s2.S < s1.S*s2.F;
  });
  dbg(p);
  vi rp(n);
  rep(i,0,n) rp[p[i]] = i;
  Tree st(n);
  for (int i = n-1; i >= 0; --i) {
    ans[pts[i].S.S] = st.query(0, rp[i]);
    st.update(rp[i], pts[i].S.F);
  }
  rep(i,0,n) {
    cout << ans[i] << '\n';
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}