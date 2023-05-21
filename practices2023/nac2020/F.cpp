#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <(b); i++)
#define trav(a,x) for(auto& a:x)
#define all(x) begin(x), end(x)
#define sz(x) (ingt) (x).size()
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
  cerr << ' ' << H; db_out(T...);
}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
const int MOD = 1e9+7;

const ll INF = 1000000000000000000LL;
void dijkstra(int s, vector<ll> &d, vector<int> &p, vector<vector<pair<int, ll>>>& adj) {
  int n = adj.size();
  d.assign(n, INF);
  p.assign(n, -1);
  d[s] = 0;
  using pii = pair<ll, int>;
  priority_queue<pii, vector<pii>, greater<pii>> q;
  q.push({0,s});
  while(!q.empty()) {
    int v = q.top().second;
    ll d_v = q.top().first;
    q.pop();
    if(d_v != d[v]) continue;
    for(auto edge: adj[v]) {
      int to = edge.first;
      ll len = edge.second;
      if(d[v] + len < d[to]) {
        d[to] = d[v] + len;
        p[to] = v;
        q.push({d[to], to});
      }
    }
  }
}


void solve() {
  ll n,k;
  cin>>n>>k;

  vector<vi> v(n,vi(n,0));
  map<int,vector<pii>> pts;
  rep(i,0,n) rep(j,0,n) {cin>>v[i][j];pts[v[i][j]].pb({i,j});}
  vector<vector<pair<int, ll>>> adj(n*n+2);
  rep(i,1,k)
  trav(a,pts[i]) trav(b,pts[i+1])
  {
    adj[a.F*n+a.S].pb({b.F*n+b.S,abs(a.F-b.F)+abs(a.S-b.S)});
  }

  trav(b,pts[1])
  adj[n*n].pb({b.F*n+b.S,0});
  trav(b,pts[k])
  adj[b.F*n+b.S].pb({n*n+1,0});

  vector<ll> d(n*n+2);
  vi p(n*n+2);
  dijkstra(n*n,d,p,adj);
  ll ans=d[n*n+1];
  if(ans==INF) ans=-1;
  cout<<ans<<"\n";
  
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}