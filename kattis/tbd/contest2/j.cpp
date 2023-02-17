#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i <(b); i++)
#define trav(a, x) for (auto& a: x)
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

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '{'; string sep; for (const auto &x: v) os << sep << x, sep = ", "; return os << '}';}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
const int MOD = 1e9+7;

/*
impl:

1) move func
for each scooter:
  2) move to spot on top/bottom of scooter
    a) on same col as scooter: move left by 1, go up/down then right
    b) go up/down until correct row, then left/right
  3) push down/up as needed
  4) move left/right by 1, up/down by 1
  5) push left/right as needed
*/

void printMove(pii dir) {
  if (dir == mp(0,1)) {
    cout << "up\n";
  } else if (dir == mp(0,-1)) {
    cout << "down\n";
  } else if (dir == mp(1,0)) {
    cout << "right\n";
  } else if (dir == mp(-1,0)) {
    cout << "left\n";
  }
}

struct game {
  vector<vector<bool>> grid;
  set<pii> scooters;
  pii d;
  pii p;

  void move(pii dir) {
    printMove(dir);
    p.F += dir.F;
    p.S += dir.S;
    pii cur = {p.F,p.S};
    while (grid[cur.F][cur.S]) {
      cur = {cur.F+dir.F, cur.S+dir.S};
    }
    if (grid[p.F][p.S]) {
      if (cur != d) {
        grid[cur.F][cur.S] = true;
        scooters.insert(cur);
      }
      scooters.erase(p);
      grid[p.F][p.S] = false;
    }
  }
};

const int G = 1000;
const int S = G/2 - 15;

void solve() {
  int n; cin >> n;
  game g;
  g.grid.assign(G, vector<bool>(G, false));
  int x0, y0, xt, yt; cin >> x0 >> y0 >> xt >> yt;
  x0 += S; y0 += S; xt += S; yt += S;
  g.d = {xt,yt};
  g.p = {x0,y0};
  rep(i,0,n) {
    int x1,y1; cin >> x1 >> y1;
    x1+=S; y1+=S;
    g.grid[x1][y1] = true;
    g.scooters.insert({x1,y1});
  }
  while (g.scooters.size() != 0) {
    pii scooter = *(g.scooters.begin());
    if (scooter.F == g.p.F) {
      // move left by 1
      g.move({-1,0});
    }
    dbg("start", scooter, g.d, g.p);
    if (scooter.S >= g.d.S) {
      // need to be on top of scooter
      if (scooter.S >= g.p.S) {
        // need to move up
        int amt = scooter.S - g.p.S + 1;
        rep(i, 0, amt) {
          g.move({0,1});
        }
      } else {
        // need to move down
        int amt = g.p.S - scooter.S - 1;
        rep(i, 0, amt) {
          g.move({0,-1});
        }
      }
    } else {
      // need to be below scooter
      if (scooter.S >= g.p.S) {
        // need to move up
        int amt = scooter.S - g.p.S - 1;
        rep(i, 0, amt) {
          g.move({0,1});
        }
      } else {
        // need to move down
        int amt = g.p.S - scooter.S + 1;
        rep(i, 0, amt) {
          g.move({0,-1});
        }
      }
    }
    dbg("lr", scooter, g.d, g.p);
    // move left/right as needed
    if (scooter.F >= g.p.F) {
      int amt = scooter.F - g.p.F;
      rep(i, 0, amt) {
        g.move({1,0});
      }
    } else {
      int amt = g.p.F - scooter.F;
      rep(i, 0, amt) {
        g.move({-1,0});
      }
    }
    dbg("du", scooter, g.d, g.p);
    // push down/up as needed
    if (scooter.S >= g.d.S) {
      // push down
      int amt = scooter.S - g.d.S;
      rep(i, 0, amt) {
        g.move({0,-1});
      }
    } else {
      // push up
      int amt = g.d.S - scooter.S;
      rep(i, 0, amt) {
        g.move({0,1});
      }
    }
    dbg("rot", scooter, g.d, g.p);
    // move left/right by 1
    if (scooter.F > g.d.F) {
      g.move({1,0});
    } else {
      g.move({-1,0});
    }
    // move up/down by 1
    if (g.p.S > g.d.S) {
      g.move({0,-1});
    } else {
      g.move({0,1});
    }
    dbg("final", scooter, g.d, g.p);
    // push left/right as needed
    if (scooter.F > g.d.F) {
      int amt = scooter.F-g.d.F;
      rep(i,0,amt) {
        g.move({-1,0});
      }
    } else {
      int amt = g.d.F-scooter.F;
      rep(i,0,amt) {
        g.move({1,0});
      }
    }
  }
}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  solve();
}