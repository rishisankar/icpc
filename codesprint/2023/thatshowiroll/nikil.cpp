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

inline int next(int v) {
  int t=v|(v-1);
  return (t+1)|(((~t & -~t)-1)>>(__builtin_ctz(v)+1));
}

vector<int> counts(26,0);
int starts=0;

void solve()
{
  int l; cin>>l;
  rep(i,0,l)
  {
    string s; cin>>s;
    int x=s[0]-'a';
    starts=starts|(1<<x);
    if(sz(s)>1)
    {
      int y=s[1]-'a';
      counts[x]=counts[x]|(1<<y);
    }
  }

  const int k=6,n=26;
  int best=0,ans=-1;
  for(int w=(1<<k)-1; w<(1<<n); w=next(w))
  {
    int cur=0;
    for (int j=w;j;j=j&(j-1))
    {
      int b=__builtin_popcount((j&(-j))-1);
      if(starts&(1<<b)) cur+=max(6,2*__builtin_popcount(counts[b]&w));
    }
    if(cur>ans) ans=cur,best=w;
  }
  rep(i,0,26) if(best&(1<<i)) printf("%c",'a'+i);
  printf("\n%.20Lf\n",ans/(long double)36);
}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  ll t; cin >> t;

  rep(i,0,t)
    solve();
}