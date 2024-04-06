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
#define int ll

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
int n,m;
vector<pii> v,w;
ll ans=0;

void dq(int l, int r, int cl, int cr)
{
  if(l>r) return;
  int m=(l+r)/2;
  pii a=v[m];
  ll so_far=-1;
  int bst = -1;
  rep(i,cl,cr+1)
  {
    bool bad=false;
    bad=bad||((w[i].F-a.F)<=0);
    bad=bad||((w[i].S-a.S)<=0);
    if (bad) continue;
    ll c=(w[i].F-a.F)*(w[i].S-a.S);
    if(c>=so_far)
    {
      bst = i;
      so_far = c;
    }
  }

  if (bst == -1) {
    dq(l,m-1,cl,cr);
    dq(m+1,r,cl,cr);
    return;
  }

  ans=max(ans,so_far);
  dq(l,m-1,cl,bst);
  dq(m+1,r,bst,cr);
}

void solve()
{
  cin>>n>>m;
  vector<pii> v1(n),v2(m);
  rep(i,0,n) cin>>v1[i].F>>v1[i].S;
  rep(i,0,m) cin>>v2[i].F>>v2[i].S;

  sort(all(v1));

  trav(a,v1)
  if(sz(v)==0 || a.S<v.back().S) v.pb(a);


  sort(all(v2), greater<pii>());
  trav(a,v2)
  if(sz(w)==0 || a.S > w.back().S) w.pb(a);
  reverse(all(w));

  n=sz(v);
  m=sz(w);

  dq(0,n-1,0,m-1);

  cout<<ans<<"\n";
}

int32_t main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  ll t=1;

  rep(i,0,t)
    solve();
}
