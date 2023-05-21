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

int n,k;
vector<string> grid;
vi sizes;
vector<pii> dirs;
ll test(int i) {
  if (i == k) {
    for (string s : grid) {
      rep(j,0,sz(s)) {
        if (s[j] == 'O') return 0;
      }
    }
    dbg(grid);
    return 1;
  }
  ll ans = 0;
  for (auto dir : dirs) {
    if (sizes[i] == 1 && dir.F == 1) continue;
    for (int x = 0; x < n; ++x) {
      for (int y = 0; y < n; ++y) {
        bool valid = true;
        vector<pii> pos;
        int nx = x, ny = y;
        rep(j,0,sizes[i]) {
          if (nx >= n || ny >= n || grid[nx][ny] == 'X' || (grid[nx][ny] >= '0' && grid[nx][ny] <= '9')) { valid = false; break; }
          pos.pb({nx,ny});
          nx += dir.F; ny += dir.S;
        }
        if (!valid) continue;
        vector<char> old;
        for (auto p : pos) {
          old.pb(grid[p.F][p.S]);
          grid[p.F][p.S] = (i+'0');
        }
        ans += test(i+1);
        rep(j,0,sz(pos)) {
          auto p = pos[j];
          grid[p.F][p.S] = old[j];
        }
      }
    }
  }
  return ans;
}

void solve() {
  dirs.pb({0,1});
  dirs.pb({1,0});
  cin >> n >> k;
  grid.resize(n);
  rep(i,0,n) cin >> grid[i];
  rep(i,0,k) {
    int x; cin >> x; sizes.pb(x);
  }
  ll ans = test(0);
  cout << ans << '\n';
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}