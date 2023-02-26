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
  ll x;
  cin>>x;

  int target;
  cin>>target;

  vi v(62);
  rep(i,0,62)
  if(x&(1LL<<i)) v[i]=1;

  int cur=__builtin_popcountll(x);  
  
  if(target>cur) // greedy fill in
  {
    int to_add=target-cur;
    rep(i,0,62)
    {
      if(v[i]==0)
      {
        v[i]=1;
        to_add--;
        if(to_add==0) break;
      }
    }
  }
  else
  {
    int to_rem=cur-target+1;
    int add_pos=-1;
    rep(i,0,62)
    {
      if(v[i]==1)
      {
        v[i]=0;
        to_rem--;
        if(to_rem==0)
        {
          add_pos=i+1;
          break;
        }
      }
    }
     
    while(v[add_pos]==1) add_pos++;
    v[add_pos]=1;

    int ct=0;
    rep(i,0,add_pos)
    {
      if(v[i]==1) ct++;
      v[i]=0;
    }
    rep(i,0,ct)
    v[i]=1;
  }

  ll ans=0;
  rep(i,0,62)
  if(v[i]) ans+=(1LL<<i);

  cout<<ans<<endl;

}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  solve();
}