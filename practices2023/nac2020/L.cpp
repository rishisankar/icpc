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
const ll INF = 1000000000000000000LL;

vector<pii> dirs{mp(0,1), mp(1,0), mp(0,-1), mp(-1,0)};  // right, down, left, up

int n,m;
vector<vector<char>> grid;
vector<vector<int>> gargrid;
vector<pii> gargoyles;
vector<bool> orient;

ll check_valid(vi& comp, vi& vis, vector<vector<pair<int,bool>>>& neighbors) {
  ll ans = 0;
  for (int x : comp) {
    vi dz;
    if (vis[x]) {
      dz.pb(3); dz.pb(1);
    } else {
      dz.pb(0); dz.pb(2);
    }
    for (int d : dz) {
      if (neighbors[x][d].F == -1) return INF;
      if (vis[neighbors[x][d].F] != neighbors[x][d].S) return INF;
    }
    if (vis[x] != orient[x]) ++ans;
  }
  return ans;
}

void run() {
  int n,m; cin >> n >> m;
  grid.assign(n+2, vector<char>(m+2, 'W'));
  gargrid.assign(n+2, vector<int>(m+2,-1));
  rep(i,0,n) {
    string s; cin >> s;
    rep(j,0,m) {
      grid[i+1][j+1] = s[j];
      if (s[j] == 'V' || s[j] == 'H') {
        gargrid[i+1][j+1] = sz(gargoyles);
        gargoyles.pb({i+1,j+1});
        orient.pb(s[j] == 'V');
      }
    }
  }
  int g = sz(gargoyles);
  vector<vector<pair<int,bool>>> neighbors(g, vector<pair<int,bool>>(4, {-1,-1})); // neighbor + orientation
  rep(i,0,g) {
    rep(j,0,4) {
      int x = gargoyles[i].F;
      int y = gargoyles[i].S;
      int d = j;
      while (true) {
        x += dirs[d].F;
        y += dirs[d].S;
        if (grid[x][y] == 'W') {
          neighbors[i][j] = {i,(j==1||j==3)};
          break;
        } else if (grid[x][y] == 'V' || grid[x][y] == 'H') {
          neighbors[i][j] = {gargrid[x][y], (d==1||d==3)};
          break;
        } else if (grid[x][y] == '#') {
          break;
        } else if (grid[x][y] == '/') {
          if (d == 0) d = 3;
          else if (d == 1) d = 2;
          else if (d == 2) d = 1;
          else if (d == 3) d = 0;
        } else if (grid[x][y] == '\\') {
          if (d == 0) d = 1;
          else if (d == 1) d = 0;
          else if (d == 2) d = 3;
          else if (d == 3) d = 2;
        }
      }
    }
  }
  ll ans = 0;
  vector<int> vis(g,-1);
  rep(i,0,g) {
    if (vis[i] != -1) continue;
    vi comp;
    vis[i] = 0;
    stack<int> s;
    s.push(i);
    while (!s.empty()) {
      int t = s.top(); s.pop();
      comp.pb(t);
      rep(d,0,4) {
        if (neighbors[t][d].F != -1) {
          if (vis[neighbors[t][d].F] == -1) {
            s.push(neighbors[t][d].F);
            bool isOr = (vis[t] == 0 && (d == 0 || d == 2)) || (vis[t] == 1 && (d == 1 || d == 3));
            vis[neighbors[t][d].F] = (isOr ? neighbors[t][d].S : (1^neighbors[t][d].S));
          }
        }
      }
    }
    ll bst = check_valid(comp, vis, neighbors);
    for (int x : comp) vis[x] ^= 1;
    bst = min(bst, check_valid(comp,vis,neighbors));
    if (bst == INF) {
      cout << -1 << '\n';
      return;
    }
    ans += bst;
  } 
  cout << ans << '\n';

}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  run();
}