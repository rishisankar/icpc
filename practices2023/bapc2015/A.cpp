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

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

const int MOD = 1000000000 + 7;
int N,W,L;

bool check(int k, vi &v)
{
  int cur_start=1;
  bool train_in_cur = false;
  int ct=1;
  rep(i,1,W+1)
  {
    if(v[i]-cur_start+1>k)
    {
      ct++;
      // if train in cur already, end at size k
      if (train_in_cur) {
        cur_start = cur_start + k;
        if (v[i]-cur_start+1 > k) {
          // still too far
          ++ct;
          cur_start = v[i];
        }
      } else {
        cur_start = v[i];
        train_in_cur = true;
      }


      // try starting at cur_start+k; if its still too long, then club all the zeros together
      // int diff=v[i]-(cur_start+k)+1;
      // if(diff<=k)
      // {
      //   cur_start=cur_start+k;
      // }
      // else
      // {
      //   cur_start=v[i];
      //   ct++;
      // }
    } else {
      train_in_cur = true;
    }
    dbg(k,i,ct);
  }
  int last=N-cur_start+1;
  if(last>k && train_in_cur) ct++;
  return (ct<=L);
}


void solve()
{
  cin>>N>>W>>L;

  vi v(W+1,-1);
  rep(i,0,W) cin>>v[i+1];

  int l=1; int r=N;
  int ans=N;
  while(l<=r)
  {
    int m=(l+r)/2;
    if(check(m,v))
    {
      ans=min(m,ans);
      r=m-1;
    }
    else
    {
      l=m+1;
    }
  }
  cout<<ans<<"\n";
}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  ll t;
  cin>>t;

  rep(i,0,t)
    solve();
}