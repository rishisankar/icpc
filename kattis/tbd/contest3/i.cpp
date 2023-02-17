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

vi val, comp, z, cont;
int Time, ncomps;
template<class G> int dfs(int j, G& g) {
  int low = val[j] = ++Time, x; z.push_back(j);
  for (auto e : g[j]) if (comp[e] < 0)
    low = min(low, val[e] ?: dfs(e,g));
  
  if (low == val[j]) {
    do {
      x = z.back(); z.pop_back();
      comp[x] = ncomps;
      cont.push_back(x);
    } while (x != j);
    // f(cont);
    cont.clear();
    ncomps++;
  }
  return val[j] = low;
}
template<class G> void scc(G& g) {
  int n = sz(g);
  val.assign(n,0); comp.assign(n, -1);
  Time = ncomps = 0;
  rep(i,0,n) if (comp[i] < 0) dfs(i,g);
}

void solve() {
  int n,e,c;
  cin >> n >> e >> c;
  vector<vi> adj(n);
  vector<vi> adjr(n);
  rep(i, 0, c) {
    int a,b; cin >> a >> b;
    adj[a].push_back(b);
    adjr[b].push_back(a);
  }
  unordered_set<int> en;
  rep(i, 0, e) {
    int x; cin >> x;
    en.insert(x);
  }
  stack<int> s;
  vector<bool> visited(n, false);
  for (int x : en) {
    s.push(x);
    visited[x] = true;
  }
  while (!s.empty()) {
    int t = s.top();
    s.pop();
    for (int x : adjr[t]) {
      if (visited[x]) continue;
      visited[x] = true;
      s.push(x);
    }
  }
  // visited conatins all you need to send private to
  int ans = 0;
  rep(i,0,n) {
    if (visited[i] && !en.count(i)) {
      ++ans;
    }
  }
  dbg("priv", ans);

  // construct remaining subgraph
  unordered_map<int,int> rem;
  unordered_set<int> rems;
  rep(i,0,n) {
    if ((!visited[i]) && (!en.count(i))) {
      rem[i] = rem.size();
      rems.insert(i);
    }
  }
  vector<vi> nadj(rem.size());
  for (int t : rems) {
    for (int x : adj[t]) {
      if (rems.count(x)) {
        nadj[rem[t]].push_back(rem[x]);
      }
    }
  }

  dbg(rems.size());
  for (int t: rems)dbg(t);
  dbg(nadj);

  scc(nadj);
  dbg("scc",ncomps);
  dbg(comp);

  vector<unordered_set<int>> adjscc(ncomps);
  unordered_set<int> invalid;
  rep(i, 0, rem.size()) {
    for (int x : nadj[i]) {
      if (comp[i] != comp[x]) {
        adjscc[comp[i]].insert(comp[x]);
        invalid.insert(comp[x]);
      }
    }
  }

  dbg(invalid.size());

  ans += (ncomps - invalid.size());

  cout << ans << '\n';


}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  solve();
}