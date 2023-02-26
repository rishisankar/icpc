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

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) 
{ os << '{'; string sep; for (const auto &x: v) os << sep << x, sep = ", "; return os << '}';}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) 
{ return os << '(' << p.first << ", " << p.second << ')'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
const int MOD = 1e9+7;

void solve() {
  int W, H, D;
  cin >> W >> H >> D;
  int grid[W][H][D];
  rep(i, 0, W) {
    rep(j, 0, H) {
      rep(k, 0, D) {
        grid[i][j][k] = 1;
      }
    }
  }
  string front[H];
  rep(j, 0, H) {
    cin >> front[j];
    rep(i, 0, W) {
      if(front[j][i] == '.') {
        rep(k, 0, D) {
          grid[i][j][k] = 0;
        }
      }
    }
  }
  string right[H];
  rep(j, 0, H) {
    cin >> right[j];
    rep(k, 0, D) {
      if(right[j][k] == '.') {
        rep(i, 0, W) grid[i][j][k] = 0;
      }
    }
  }
  string top[D];
  for(int k = D-1; k >= 0; k--) {
    cin >> top[k];
    rep(i, 0, W) {
      if(top[k][i] == '.') {
        rep(j, 0, H) grid[i][j][k] = 0;
      }
    }
  }

  bool ok;
  rep(j, 0, H) {
    rep(i, 0, W) {
      if(front[j][i] == '#') {
        ok = false;
        rep(k, 0, D) {
          if(grid[i][j][k]) ok = true;
        }
        if(!ok) {
          cout << "invalid" << endl;
          return;
        }
      }
    }
  }
  rep(j, 0, H) {
    rep(k, 0, D) {
      if(right[j][k] == '#') {
        ok = false;
        rep(i, 0, W) if(grid[i][j][k]) ok = true;
        if(!ok) {
          cout << "invalid" << endl;
          return;
        }
      }
    }
  }
  for(int k = D-1; k >= 0; k--) {
    rep(i, 0, W) {
      if(top[k][i] == '#') {
        ok = false;
        rep(j, 0, H) if(grid[i][j][k]) ok = true;
        if(!ok) {
          cout << "invalid" << endl;
          return;
        }
      }
    }
  }

  int ans = 0;
  rep(i, 0, W) {
    rep(j, 0, H) {
      rep(k, 0, D) {
        ans += grid[i][j][k];
      }
    }
  }
  cout << ans << endl;
}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  solve();
}