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
  int n; cin >> n;
  vector<string> w(n);
  rep(i,0,n) cin >> w[i];
  unordered_map<string,vector<int>> rep;
  bool d = 1;
  int bst = 10000000;
  rep(i,0,n) {
    rep[w[i]].pb(i);
  }
  for (auto& p : rep) {
    if (sz(p.S) > 1) {
      d = 0;
      rep(i, 0, sz(p.S)-1) {
        bst = min(bst, p.S[i+1]-p.S[i]);
      }
    }
  }
  if (bst == 10000000) {
    cout << "0\n";
    return;
  }
  cout << (n-bst) << '\n';

}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}