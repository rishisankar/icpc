#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define F first
#define S second
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<long long> vi;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '{'; string sep; for (const auto &x : v) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef NIKIL_DEBUG
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

// issue there may be shortest path 4 and 6, cant do compare btwn 4/5 and 5/6

const ll INF = 1e14;
const ll DINF = (ll)1e18;
vector<vector<pair<ll, ll>>> adj;

void dijkstra(ll s, vector<ll> &d, ll c) {
    ll n = adj.size();
    d.assign(n, DINF);

    d[s] = 0;
    using pii = pair<ll, ll>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s});
    while (!q.empty()) {
        ll v = q.top().second;
        ll d_v = q.top().first;
        q.pop();
        if (d_v != d[v])
            continue;

        for (auto edge : adj[v]) {
            ll to = edge.first;
            ll len = edge.second+c;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                q.push({d[to], to});
            }
        }
    }
}

void solve()
{
  int n,m;
  cin>>n>>m;

  adj=vector<vector<pair<ll, ll>>>(n);
  rep(i,0,m)
  {
    ll a,b,l;
    cin>>a>>b>>l;
    a--;b--;
    adj[a].pb({b,l});
    adj[b].pb({a,l});
  }

  vi dp(n,INF);
  vi best_path(n+1,INF);
  vector<bool> on_some_shortest_path(n,false);
  on_some_shortest_path[0]=on_some_shortest_path[n-1]=true;
  dp[0]=0;
  rep(t,0,n)
  {
    vi ndp=dp;
    rep(i,0,n)
    trav(a,adj[i])
    ndp[a.F]=min(ndp[a.F],dp[i]+a.S);
    dp=ndp;
    best_path[t+1]=dp[n-1];
  }

  set<ll> vals;
  rep(i,1,n+1)
  {
    vals.insert(best_path[i-1]-best_path[i]);
    vals.insert(best_path[i-1]-best_path[i]+1);
    vals.insert(max(0LL,best_path[i-1]-best_path[i]-1));
  }

  vals.insert(0);
  vals.insert(INF);

  trav(c,vals)
  {
    vi d1,d2;
    dijkstra(0,d1,c);
    dijkstra(n-1,d2,c);
    assert(d1[n-1]==d2[0]);
    rep(j,0,n)
    if(d1[j]+d2[j]==d1[n-1] && d1[j] < DINF && d2[j] < DINF && d1[n-1] < DINF)
    on_some_shortest_path[j]=true;
  }

  vi ans;
  rep(i,0,n)
  if(!on_some_shortest_path[i]) ans.pb(i+1);

  cout<<sz(ans)<<"\n";
  trav(a,ans) cout<<a<<" ";
  if(sz(ans)!=0)
  cout<<"\n";
}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  ll t=1;

  rep(i,0,t)
    solve();
}
