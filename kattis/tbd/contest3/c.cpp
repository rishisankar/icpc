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

const int INF = 1e9;
vector<vector<pii>> adj;
int sml = INF;
void dijkstra(int s, vector<int>& d, vector<int> &p) {
  int n = adj.size();
  d.assign(n, -1);
  p.assign(n, -1);

  d[s] = INF;
  priority_queue<pii, vector<pii>> q;
  q.push({INF, s});
  while (!q.empty()) {
    int v = q.top().S;
    int d_v = q.top().F;
    q.pop();
    if (d_v != d[v]) continue;
    for (auto edge : adj[v]) {
      int to = edge.first;
      int len = edge.second;
      if (min(d[v], len) > d[to]) {
        d[to] = min(d[v], len);
        p[to] = v;
        q.push({d[to], to});
      }
    }
  }
}

void solve() {
  int n, m; cin >> n >> m;
  adj.resize(n);
  map<pii, int> edi;
  rep(i,0,m) {
    int a,b,c; cin >> a >> b >> c;
    adj[a].push_back({b,c});
    adj[b].push_back({a,c});
    edi[{a,b}] = edi[{b,a}] = i;
    sml = min(sml, c);
  }
  vector<int> d,p;
  dijkstra(0, d, p);
  dbg(d);
  dbg(p);

  vector<int> path;
  int cur = n-1;
  while (cur != 0) {
    path.push_back(cur);
    cur = p[cur];
  }
  path.push_back(0);
  reverse(all(path));

  unordered_set<int> en;
  rep(i,0,path.size()) {
    int x = path[i];
    for (pii j : adj[x]) {
      dbg(x,j);
      if (i > 0 && j.F == path[i-1]) continue;
      if (i < path.size()-1 && j.F == path[i+1]) continue;
      dbg(x,j);
      en.insert(edi[{x,j.F}]);
    }
  }
  vector<int> env;
  for (int x : en) env.push_back(x);
  sort(all(env));
  dbg(path);
  dbg(env);


  if (env.size() == 0) {
    cout << "none\n";
  } else {
    for (int x : env) cout << x << ' ';
    cout << '\n';
  }

}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  solve();
}