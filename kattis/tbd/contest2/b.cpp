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

vi centroid(vector<vi> &g) {
  int n = g.size();
  vi centroid;
  vi ss(n);
  function<void (int, int)> dfs = [&](int u, int prev) {
    ss[u] = 1;
    bool is_centroid = true;
    for (auto v : g[u]) if (v != prev) {
      dfs(v,u);
      ss[u] += ss[v];
      if (ss[v] > n/2) is_centroid =false;
    }
    if (n-ss[u] > n/2) is_centroid = false;
    if (is_centroid) centroid.push_back(u);
  };
  dfs(0,-1);
  return centroid;
}

void solve() {
  int n;
  cin>>n;

  vector<vi> g(n);
  rep(i,0,n-1)
  {
    int a,b;
    cin>>a>>b;
    a--;b--;
    g[a].pb(b);
    g[b].pb(a);
  }

  vi cent=centroid(g);
  int c=cent[0];

  queue<pii> q;
  vector<bool> vis(n,false);
  vis[c]=true;
  q.push({c,0});
  map<int,vi> dists;
  dists[0].pb(c);
  while(!q.empty())
  {
    pii x=q.front();
    q.pop();
    trav(a,g[x.F])
    {
      if(!vis[a])
      {
        vis[a]=true;
        q.push({a,x.S+1});
        dists[x.S+1].pb(a);
      }
    }
  }

  vi whites;
  vi blacks;
  trav(a,dists)
  {
    if(a.F%2==0)
    {
      trav(b,a.S) whites.pb(b);
    }
    else
    {
      trav(b,a.S) blacks.pb(b);
    }
  }

  if(sz(whites)<2 || sz(blacks)<2)
  {
    cout<<"NO\n";
    exit(0);
  }

  unsigned seed=std::chrono::system_clock::now().time_since_epoch().count();
  shuffle(all(whites),std::default_random_engine(seed));
  shuffle(all(blacks),std::default_random_engine(seed));

  cout<<"YES\n";
  int w=sz(whites),b=sz(blacks);
  dbg(w,b);
  // rep(i,0,(w+1)/2)
  // {
  //   cout<<whites[i]+1<<" ";
  //   if((w+1)/2+i<w)
  //   cout<<whites[(w+1)/2+i]+1<<" ";
  // }
  // rep(i,0,(b+1)/2)
  // {
  //   cout<<blacks[i]+1<<" ";
  //   if((b+1)/2+i<b)
  //   cout<<blacks[(b+1)/2+i]+1<<" ";
  // }

  trav(a,whites)
  cout<<a+1<<" ";
  trav(a,blacks)
  cout<<a+1<<" ";
  cout<<endl;
}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  solve();
}