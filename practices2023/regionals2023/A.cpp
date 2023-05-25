#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <(b); ++i)
#define trav(a,x) for(auto& a:x)
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

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) {
  return os<< '(' << p.first << ", " << p.second << ')';
}
template<typename T> ostream & operator<<(ostream &os, const vector<T> &v) {
  os << '{';
  string sep;
  for(const auto &x: v) os << sep << x, sep = ", ";
  return os << '}';
}

void dbg_out() {cerr << endl;}
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) {
  cerr << ' ' << H; dbg_out(T...);
}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

const int MOD = 1e9+7;
int n;
map<int,char> invm;
set<char> remaining;


void dfs(int idx, map<int,set<int>> &can, vi &coloring, vector<vi> &g, vi &cts)
{
  if(idx==n)
  {
    string a,b,c;
    rep(i,0,n)
    if(coloring[i]==0) a+=invm[i];
    rep(i,0,n)
    if(coloring[i]==1) b+=invm[i];
    rep(i,0,n)
    if(coloring[i]==2) c+=invm[i];

    while(sz(a)<6) {a+=*remaining.begin(); remaining.erase(remaining.begin());}
    while(sz(b)<6) {b+=*remaining.begin(); remaining.erase(remaining.begin());}
    while(sz(c)<6) {c+=*remaining.begin(); remaining.erase(remaining.begin());}

    cout<<a<<" "<<b<<" "<<c<<"\n";
    exit(0);
  }

  if(sz(can[idx])==0) return;

  trav(c,can[idx])
  {
    if(cts[c]==6) continue;
    set<int> to_add_back;
    trav(a,g[idx])
    {
      if(can[a].find(c)!=can[a].end())
      {
        to_add_back.insert(a);
        can[a].erase(c);
      }
    }
    cts[c]++;
    coloring[idx]=c;
    dfs(idx+1,can, coloring, g, cts);
    coloring[idx]=-1;
    cts[c]--;
    trav(a,to_add_back)
    can[a].insert(c);
  }
}

void solve() {
  int N;
  cin>>N;

  vector<vi> g;
  map<char,int> m;

  rep(i,0,26) remaining.insert('a'+i);

  rep(i,0,N)
  {
    string s;
    cin>>s;
    rep(j,0,3)
    if(m.find(s[j])==m.end())
    {
      remaining.erase(s[j]);
      m[s[j]]=sz(m);
      invm[m[s[j]]]=s[j];
      g.pb(vi());
    }
    
    rep(j,0,3)
    rep(k,j+1,3)
    {
      if(s[j]==s[k])
      {
        cout<<0<<"\n";
        exit(0);
      }
      g[m[s[j]]].pb(m[s[k]]);
      g[m[s[k]]].pb(m[s[j]]);
    }
  }

  if(sz(m)>18)
  {
    cout<<0<<"\n";
    exit(0);
  }

  n=sz(m);

  map<int,set<int>> can;
  rep(i,0,n)
  rep(j,0,3) can[i].insert(j);

  vi coloring(n,-1);
  vi cts(3,0);

  dfs(0,can,coloring,g,cts);
  cout<<0<<"\n";
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}