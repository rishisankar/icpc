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

const ll MOD = 1e9+7;

void solve()
{
  ll n,m,k;
  cin>>n>>m>>k;

  if((k%n==0)||(k%m==0))
  {
    cout<<1<<endl;
    return;
  }

  rep(i,1,m)
  {
    if(n*i>=k) break;
    ll rem=k-n*i;
    if(rem%(m-i)==0)
    {
      cout<<2<<endl;
      return;
    }
  }

  rep(i,1,n)
  {
    if(m*i>=k) break;
    ll rem=k-m*i;
    if(rem%(n-i)==0)
    {
      cout<<2<<endl;
      return;
    }
  }

  k=n*m-k;

  rep(i,1,m)
  {
    if(n*i>=k) break;
    ll rem=k-n*i;
    if(rem%(m-i)==0)
    {
      cout<<2<<endl;
      return;
    }
  }

  rep(i,1,n)
  {
    if(m*i>=k) break;
    ll rem=k-m*i;
    if(rem%(n-i)==0) 
    {
      cout<<2<<endl;
      return;
    }
  }

  cout<<3<<endl;
  return;

}

int main()
{

  solve(); 
}