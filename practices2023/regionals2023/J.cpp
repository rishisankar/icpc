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
int b, p;

int ans(vi &t, int maxc) {
  vector<vi> start(2, vi(maxc+1)); // k = start[i][j] represents dp[j][k] at pos i, dp[j][k] is pos, neg
  vector<vi> prev(2, vi(maxc+1, 0));
  vector<vi> cur;
  rep(i, 0, 2) {
    rep(j, 0, maxc+1) {
      start[i][j] = maxc+1;
    }
  }
  rep(d, 0, p) {
    cur = start;
    rep(j, t[d], maxc+1) {
      cur[0][j] = min(cur[0][j], prev[0][j-t[d]]);
    }
    rep(j, t[d]+1, maxc+1) {
      cur[1][j] = min(cur[1][j], prev[0][j-t[d]-1]);
    }
    rep(j, 0, maxc+1) {
      cur[0][j] = min(cur[0][j], prev[1][j]+b-t[d]);
      cur[1][j] = min(cur[1][j], prev[1][j]+b-t[d]-1);
    }
    swap(prev, cur);
  }
  int ans = maxc+1;
  dbg(prev);
  rep(j, 0, maxc+1) {
    ans = min(ans, max(j, prev[0][j]));
  }
  return ans;
}


void solve() {
  cin >> b >> p;
  vi t1(p), t2(p);
  rep(i, 0, p) {
    cin >> t1[i];
  }
  int i = p;
  bool zero = true;
  while(i--) {
    if(zero && t1[i] == 0) t2[i] = 0;
    else {
      t2[i] = b-t1[i];
      if(!zero) t2[i]--;
      else zero = false;
    }
  }
  int maxc = 0;
  int c = 0;
  rep(i, 0, p) {
    c += t1[i];
    maxc += t2[i];
  }
  maxc = max(c, maxc);
  
  cout << min(ans(t1, maxc), ans(t2, maxc)) << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}