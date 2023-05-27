#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<(b) ; ++i)
#define trav(a,x) for(auto &a:x)
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

void solve() {
  int n,m,k;
  cin>>n>>m>>k;

  vector<vi> g(n); vector<vi> grev(n);
  set<int> iron, coal;
  rep(i,0,m)
  {
    int x;
    cin>>x;
    x--;
    iron.insert(x);
  }
  rep(i,0,k)
  {
    int x;
    cin>>x;
    x--;
    coal.insert(x);
  }
  rep(i,0,n)
  {
    int t;
    cin>>t;
    rep(j,0,t)
    {
      int x;
      cin>>x;
      x--;
      g[i].pb(x);
      grev[x].pb(i);
    }
  }

  const int INF=1e8;
  vector<int> dcoals(n,INF);
  queue<int> q;
  trav(a,coal)
  {
    q.push(a);
    dcoals[a]=0;
  }
  while(!q.empty())
  {
    int x=q.front();
    q.pop();
    trav(a,grev[x])
    {
      if(dcoals[a]==INF)
      {
        dcoals[a]=dcoals[x]+1;
        q.push(a);
      }
    }
  }

  vector<int> dirons(n,INF);
  q=queue<int>();
  trav(a,iron)
  {
    q.push(a);
    dirons[a]=0;
  }
  while(!q.empty())
  {
    int x=q.front();
    q.pop();
    trav(a,grev[x])
    {
      if(dirons[a]==INF)
      {
        dirons[a]=dirons[x]+1;
        q.push(a);
      }
    }
  }

  vector<int> d(n,INF);
  q=queue<int>();
  q.push(0);
  d[0]=0;
  while(!q.empty())
  {
    int x=q.front();
    q.pop();
    trav(a,g[x])
    {
      if(d[a]==INF)
      {
        d[a]=d[x]+1;
        q.push(a);
      }
    }
  }

  int ans=INF;
  rep(i,0,n)
  ans=min(ans,d[i]+dcoals[i]+dirons[i]);

  if(ans==INF)
  {
    cout<<"impossible"<<"\n";
  }
  else
  {
    cout<<ans<<"\n";
  }

  
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}