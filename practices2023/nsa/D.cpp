#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a,x) for (auto& a: x)
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
	return os << '(' << p.first << ", " << p.second << ')';
}
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) {
	os << '{';
	string sep;
	for (const auto &x: v) os << sep << x, sep = ", ";
	return os << '}';
}

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) {
	cerr << ' ' << H; dbg_out(T...);
}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
const int MOD = 1e9+7;

void solve() {
  string s1, s2, s3, ty;
  string cn;
  string bn;
  unordered_map<string,int> nm;
  vector<string> nmr;
  vector<pair<string,string>> edges;
  while (cin >> ty) {
    if (ty == "N") {
      cin >> cn;
      nm[cn] = sz(nm);
      nmr.pb(cn);
    } else if (ty == "UE") {
      cin >> s1;
      cin >> s2;
      edges.pb({cn, s2});
    } else {
      bn = cn;
    }
  }
  int n = sz(nm);
  vector<vi> adj(n);
  for (auto& p : edges) {
    adj[nm[p.F]].pb(nm[p.S]);
  }
  int bug = nm[bn];
  queue<int> q;
  q.push(0);
  vi par(n, -1);
  par[0] = -2;
  while (!q.empty()) {
    int t = q.front(); q.pop();
    for (int x : adj[t]){
      if (par[x] == -1) {
        par[x] = t;
        q.push(x);
      }
    }
  }
  vector<string> ans;
  int c = bug;
  while (c != -2) {
    ans.pb(nmr[c]);
    c = par[c];
  }
  reverse(all(ans));
  for (string s : ans) cout << s << '\n';

}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	solve();
}