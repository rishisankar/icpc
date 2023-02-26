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
const ll MOD = 1e9+7;

void solve() {
  int n;
  cin>>n;

  map<int,vector<pair<int,vi>>> proofs;
  vi len;
  int id=0;
  vector<vi> proof_ids(n);
  rep(i,0,n)
  {
    int p;
    cin>>p;
    rep(j,0,p)
    {
      proof_ids[i].pb(id);
      int l;
      cin>>l;
      len.pb(l);
      int d;
      cin>>d;
      vi deps(d);
      rep(k,0,d)
      cin>>deps[k];
      proofs[i].pb({len[id],deps});
      id++;
    }
  }

  rep(i,0,n)
  dbg(proofs[i]);

  dbg(proof_ids);

  vector<vi> g(id);
  vi indeg(id,0);
  set<int> dests;
  rep(i,0,n)
  rep(j,0,sz(proofs[i]))
  {
    int x=proof_ids[i][j];
    if(i==0) dests.insert(x);
    trav(k,proofs[i][j].S)
    rep(l,0,sz(proofs[k]))
    {
      int y=proof_ids[k][l];
      g[y].pb(x);
      indeg[x]++;
    }
  }

  dbg(g);

  vector<int> dp(id,-1);
  queue<int> q;
  rep(i,0,id)
  if(indeg[i]==0)
  {
    q.push(i);
    dp[i]=len[i];
  }

  int ans=MOD;
  while(!q.empty())
  {
    int x=q.front();
    dbg(x);
    q.pop();
    if(dests.find(x)!=dests.end())
    ans=min(ans,dp[x]);

    trav(a,g[x])
    {
      if(dp[a]==-1) dp[a]=len[a];
      dp[a]+=dp[x];
      indeg[a]--;
      if(indeg[a]==0)
      {
        q.push(a);
      }
    }
  }

  cout<<ans<<endl;
  dbg(len);
  dbg(dp);


}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  solve();
}