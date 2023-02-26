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

void print(int x) {
  cout << (x+1) << ' ';
}

void solve() {
  int n; cin >> n;
  vector<vector<int>> adj(n);
  rep(i,0,n-1) {
    int a,b; cin >> a >> b;
    --a;--b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  queue<int> q;
  vector<bool> visited(n, false);
  q.push(0);
  visited[0] = true;
  int t = 0;
  while (!q.empty()) {
    t = q.front();
    q.pop();
    for (int x : adj[t]) {
      if (visited[x]) continue;
      q.push(x);
      visited[x] = true;
    }
  }
  vector<int> dist(n, 0);
  queue<pii> q2;
  visited.assign(n, false);
  visited[t] = true;
  q2.push({t,0});
  
  while(!q2.empty()) {
    pii pt = q2.front();
    q2.pop();
    for (int x : adj[pt.F]) {
      if (visited[x]) continue;
      dist[x] = 1 + pt.S;
      visited[x] = true;
      q2.push({x, dist[x]});
    }
  }

  int t2 = -1;
  rep(i,0,n) {
    if (dist[i] == 3) {
      t2 = i;
      break;
    }
  }
  if (t2 == -1) {
    cout << "NO\n";
    return;
  }
  cout << "YES\n";
  dbg(dist, t2, t);
  vector<int> pts;
  pts.push_back(t2);
  // t, t2 are the endpoints
  for (int x : adj[t2]) {
    if (dist[x] == 2) {
      pts.push_back(x);
      break;
    }
  }
  for (int x : adj[pts[1]]) {
    if (dist[x] == 1) {
      pts.push_back(x);
      break;
    }
  }
  pts.push_back(t);
  dbg(pts);

  print(pts[1]);
  print(pts[0]);
  print(pts[2]);
  print(pts[3]);

  unordered_set<int> ps;

  for (int x : pts) {
    ps.insert(x);
  }

  visited.assign(n, false);
  // run dfs from t
  stack<int> s;
  s.push(t);
  visited[t] = true;
  while (!s.empty()) {
    int l = s.top();
    s.pop();
    if (!ps.count(l)) print(l);
    for (int x : adj[l]) {
      if (visited[x]) continue;
      visited[x] = true;
      s.push(x);
    }
  }

  cout << "\n";

}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  solve();
}