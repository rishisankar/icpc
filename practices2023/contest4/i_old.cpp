#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i <(b); i++)
#define trav(a, x) for(auto &a: x)
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

template<typename T> ostream& operator << (ostream &os, const vector<T> &v) { os << '{'; string sep; for(const auto &x: v) os << sep << x, sep = ", "; return os << '}';}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...);}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

const int MOD = 1e9+7;
void solve()
{
  int n;
  cin>>n;

  unordered_set<int> left;
  rep(i,0,n) left.insert(i);

  vector<unordered_set<int>> losses(n);
  rep(j,1,n)
  {
    string xx;
    cin>>xx;
    rep(i,0,j)
    {
      int x=(xx[i]-'0');

      if(x)
      {
        losses[i].insert(j);
      }
      else
      {
        losses[j].insert(i);
      }
    }
  }
  

  ll ans=0, cur=0;
  vi l(n,0),r(n,0);
  rep(i,0,n)
  l[i]=sz(losses[i]);
  // rep(i,0,n)
  // r[i]=sz(wins[i]);

  rep(t,0,n)
  {
    set<pii> vals;
    trav(a,left)
    {
      vals.insert({l[a]-r[a],a});
    }

    pii xx=*vals.begin();
    dbg(xx);
    int x=xx.S;
    cur=ans+xx.F;
    ans=max(ans,cur);
    left.erase(x);

    trav(a,left)
    {
      if(losses[a].find(x)!=losses[a].end())
      l[a]--;
      else
      r[a]++;
    }
  }

  cout<<ans<<endl;

  
}

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  solve(); 
}