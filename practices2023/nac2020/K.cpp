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

template<class T>
struct RMQ {
  vector<vector<T>> jmp;
  RMQ(const vector<T>& V) : jmp(1,V) {
    for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
      jmp.emplace_back(sz(V) - pw * 2 + 1);
      rep(j,0,sz(jmp[k])) jmp[k][j] = min(jmp[k-1][j], jmp[k-1][j+pw]);
    }
  }
  T query(int a, int b) {
    assert(a<b);
    int dep = 31 - __builtin_clz(b-a);
    return min(jmp[dep][a], jmp[dep][b-(1<<dep)]);
  }
};

struct LCA {
  int T = 0;
  vi time, path, ret;
  RMQ<int> rmq;

  LCA(vector<vi>& C) : time(sz(C)), rmq((dfs(C,0,-1), ret)) {}
  void dfs(vector<vi>& C, int v, int par) {
    time[v] = T++;
    for (int y : C[v]) if (y != par) {
      path.push_back(v), ret.push_back(time[v]);
      dfs(C,y,v);
    }
  }
  int lca(int a, int b) {
    if (a == b) return a;
    tie(a,b) = minmax(time[a], time[b]);
    return path[rmq.query(a,b)];
  }
  // dist(a,b) return depth[a] + depth[b] - 2*depth[lca(a,b)]
};

void dfs(vector<vi>& adj, vi& d, int t, int p) {
  for (int x : adj[t]) if (x != p) {
    d[x] = d[t]+1;
    dfs(adj,d,x,t);
  }
}

void solve() {
  int n,q; cin >> n >> q;
  vector<vi> adj(n);
  rep(i,0,n-1) {
    int a,b; cin >> a >> b; --a; --b;
    adj[a].pb(b); adj[b].pb(a);
  }
  vi d(n);
  dfs(adj,d,0,-1);
  dbg(d);
  LCA l(adj);
  rep(i,0,q) {
    int a,b; cin >> a >> b; --a; --b;
    int c = l.lca(a,b);
    ll dist = d[a] + d[b] - 2*d[c] + 1;
    ll ans = n + dist*(dist-1) / 2;
    cout << ans << '\n';
  }
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}