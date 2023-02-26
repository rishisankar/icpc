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
  ll n,m,k;
  cin>>n>>m>>k;

  if(n==1)
  {
    cout<<1<<endl;
    return;
  }

  if(k==1)
  {
    cout<<(n*(n+1))/2<<endl;
    return;
  }

  ll ones=0,twos=0,big=0;
  if(m==1)
  {
    big=n;
  }
  else
  {
    ones=min(m-1,n-1);
    big=n-ones;
    if(big%k==0)
    {
      big-=1;
      ones--;
      twos++;
    }
  }

  dbg(big,twos,ones);

  ll ans=0;
  if(twos)
  {
    ll rounds=big/k;
    ans+=rounds*(ones+2);
    ll extra=big%k;
    ans+=rounds*extra;
    ans+=k*((rounds*(rounds+1))/2);

    if(extra==1)
    {
      ans+=(ones+1)+2;
      ans+=(ones+1);
    }
    if(extra>1)
    {
      ans+=(ones+extra)+2;
      ans+=(ones+2);
    }

    ans+=(ones*(ones+1))/2;
  }
  else
  {
    ll rounds=big/k;
    ans+=rounds*(ones);
    ll extra=big%k;
    ans+=rounds*extra;
    ans+=k*((rounds*(rounds+1))/2);
    
    if(extra!=0)
    ans+=(ones+extra);
  
    ans+=(ones*(ones+1))/2;
  }

  cout<<ans<<endl;
}

int main()
{

  solve(); 
}