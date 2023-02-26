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
const int MOD = 1e9+7;

void solve() {
  int n=1000005;

  vi v1(n,0),v2(n,0);
  int k;
  cin>>k;
  rep(i,0,k)
  {
    int x;
    cin>>x;
    v1[x]=1;
  }
  cin>>k;
  rep(i,0,k)
  {
    int x;
    cin>>x;
    v2[x]=1;
  }

  int ans=0;
  bool a=false,b=false;
  rep(i,0,n)
  {
    if((!v1[i]) && (!v2[i])) continue;
    if((v1[i]) && (v2[i]))
    {
      ans++;
      a=false;
      b=false;
    }
    if((v1[i]) && (!v2[i]))
    {
      if(!b)
      {
        ans++;
        a=false;
        b=true;
      }
    }
    if((!v1[i]) && (v2[i]))
    {
      if(!a)
      {
        ans++;
        a=true;
        b=false;
      }
    }
  }

  cout<<ans<<endl;

}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  solve();
}