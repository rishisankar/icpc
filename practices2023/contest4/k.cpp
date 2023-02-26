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
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; db_out(T...);}

#ifdef TTL
#define dbg(...) cerr << "(" << #___VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

const int MOD = 1e9+7;
void solve()
{
  int n,m,s,d;
  cin>>n>>m>>s>>d;

  vi v(s);
  vector<pii> slots;
  rep(i,0,s)
  {
    cin>>v[i];
    slots.pb({v[i],i});
  }

  sort(all(slots));
  vi ans(s,0);

  int extra=0;
  rep(i,0,s)
  {
    if(n>0)
    {
      int take=min(n,d-slots[i].F);
      n-=take;
      ans[slots[i].S]+=take;
    }
    else
    {
      extra+=slots[i].F;
    }
  }

  if(extra>=m)
  {
    trav(a,ans)
    cout<<a<<" ";
    cout<<endl;
  }
  else
  {
    cout<<"impossible\n";
  }
  
}

int main()
{
  
  solve(); 
}