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
typedef vector<int> vi;
 
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '{'; string sep; for (const auto &x : v) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
 
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
 
#ifdef NIKIL_DEBUG
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
 
const int MOD = 1000000000 + 7;
 
int n, k;
vector<vector<int>> g;
vector<int> mt;
vector<bool> used;
 
bool try_kuhn(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (int to : g[v]) {
        if (mt[to] == -1 || try_kuhn(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}
 
void solve()
{
  int N;
  cin>>N;
 
  vi v1(N),v2(N);
  rep(i,0,N) {cin>>v1[i];v1[i]--;}
  rep(i,0,N) {cin>>v2[i];v2[i]--;}
 
  int c1=0;
  vi idx1(N,-1);
  rep(i,0,N)
  {
    if(idx1[i]==-1)
    {
      int j=i;
      while(idx1[j]!=c1)
      {
        idx1[j]=c1;
        j=v1[j];
      }
      c1++;
    }
  }
 
  int c2=0;
  vi idx2(N,-1);
  rep(i,0,N)
  {
    if(idx2[i]==-1)
    {
      int j=i;
      while(idx2[j]!=c2)
      {
        idx2[j]=c2;
        j=v2[j];
      }
      c2++;
    }
  }
 
  dbg(idx1,idx2);
 
  vector<vector<int>> g=vector<vector<int>>(c1);
 
  map<pii,int> rev;
 
  rep(i,0,N)
  {
    g[idx1[i]].pb(idx2[i]);
    rev[mp(idx1[i],idx2[i])]=i;
  }
 
  n=c1;
  k=c2;
 
    mt.assign(k, -1);
    vector<bool> used1(n, false);
    for (int v = 0; v < n; ++v) {
        for (int to : g[v]) {
            if (mt[to] == -1) {
                mt[to] = v;
                used1[v] = true;
                break;
            }
        }
    }
    for (int v = 0; v < n; ++v) {
        if (used1[v])
            continue;
        used.assign(n, false);
        try_kuhn(v);
    }
 
  set<int> keep;
  rep(i,0,N) keep.insert(i);
 
    for (int i = 0; i < k; ++i)
        if (mt[i] != -1)
          keep.erase(rev[mp(mt[i],i)]);
 
  cout<<sz(keep)<<"\n";
  trav(a,keep) cout<<a+1<<" ";
  cout<<"\n";
 
 
}
 
int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  ll t=1;
 
  rep(i,0,t)
    solve();
}