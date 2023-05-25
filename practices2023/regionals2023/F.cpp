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

vector<vi> treeJump(vi& P) {
  int on = 1, d = 1;
  while (on < sz(P)) on *= 2, d++;
  vector<vi> jmp(d, P);
  rep(i,1,d) rep(j,0,sz(P))
    jmp[i][j] = jmp[i-1][jmp[i-1][j]];
  return jmp;
}
int jmp(vector<vi>& tbl, int nod, int steps) {
  rep(i,0,sz(tbl))
    if (steps&(1<<i)) nod = tbl[i][nod];
  return nod;
}

void solve() {
  int n,q; cin >> n >> q;
  vector<bool> reachable(n), alive(n,true);
  vector<vector<int>> adj(n);
  rep(i,0,n-1) {
    int a,b; cin >> a >> b; --a; --b;
    if (a < b) swap(a,b);
    adj[b].pb(a);
  }
  rep(i,0,n) {
    sort(all(adj[i]), greater<int>());
  }
  dbg(adj);
  int c = 0;
  reachable[0] = 1;
  while (sz(adj[c]) != 0) {
    c = adj[c].back();
    reachable[c] = 1;
  }
  vi depth(n), par(n);
  depth[0] = 1;
  par[0] = 0;
  stack<int> s;
  s.push(0);
  while (!s.empty()) {
    int t = s.top(); s.pop();
    for (int x : adj[t]) {
      depth[x] = depth[t] + 1;
      par[x] = t;
      s.push(x);
    }
  }
  vector<vi> tbl = treeJump(par);
  dbg(depth);
  dbg(par);
  rep(Z,0,q) {
    int t; cin >> t; --t;
    if (!alive[t]) {
      cout << Z << '\n';
      return;
    }
    if (reachable[t]) continue;
    dbg(Z);
    // binary search to find first nonreachable
    int lo = 2, hi = depth[t], bst = depth[t];
    while (lo <= hi) {
      int mid = (lo+hi)/2;
      int z = jmp(tbl, t, depth[t]-mid);
      if (!reachable[z]) {
        bst = z;
        hi = mid - 1;
      } else {
        lo = mid+1;
      }
    }
    int zp = par[bst];
    dbg(Z,bst,zp);
    dbg(adj[zp]);
    stack<int> st;
    while (adj[zp].back() != bst) {
      st.push(adj[zp].back());
      adj[zp].pop_back();
    }
    dbg("p2");
    while (!st.empty()) {
      int zz = st.top(); st.pop();
      dbg(zz, adj[zz]);
      alive[zz] = false;
      for (int x : adj[zz]) {
        st.push(x);
      }
    }
    dbg("p3");
    reachable[bst] = 1;
    while (sz(adj[bst]) != 0) {
      bst = adj[bst].back();
      reachable[bst] = 1;
    }
  }
  cout << q << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}