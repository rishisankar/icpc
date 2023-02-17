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

#define int ll

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


const int INF = 1e9;
vector<vector<pii>>  adj;
void dijkstra(int s, vi &d, vi &num)
{
  int n = adj.size();
  d.assign(n, INF);
  num.assign(n, -1);
  d[s] = 0;
  num[s] = 1;
  priority_queue<pii, vector<pii>, greater<pii>> q;
  q.push({0, s});
  while(!q.empty()) {
    int v = q.top().second;
    int dv = q.top().first;
    q.pop();
    if(dv != d[v]) continue;
    for(auto [to, len]: adj[v]) {
      if(d[v] + len < d[to]) {
        d[to] = d[v] + len;
        num[to] = num[v];
        q.push({d[to], to});
      }
      else if(d[v] + len == d[to]) {
        num[to] += num[v];
      }
    }
  }
}


void solve() {
  int n, m;
  cin >> n >> m;
  adj.resize(n+1);
  int a, b;
  int len = INF;
  int cycles = 0;
  vi d(n+1);
  vi num(n+1);
  rep(i, 0, m) {
    cin >> a >> b;
  
    dijkstra(a, d, num);
    dbg(num);
    if(d[b]+1 < len) {
      len = d[b]+1;
      cycles = num[b];
    }
    else if(d[b]+1 == len) {
      cycles += num[b];
    }

    adj[a].push_back({b, 1});
    adj[b].push_back({a, 1});
  }
  cout << cycles << endl;
}

int32_t main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  solve();
}
