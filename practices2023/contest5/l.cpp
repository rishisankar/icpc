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
typedef long double ld;

ll fl(ll a, ll b) {
  if (a >= 0) {
    return a*b/100;
  } else if (b == 0) {
    return 0;
  } else {
    return (a*b+1)/100 - 1;
  }
}
/*
-100 --> -1
-99 --> -1
-101 --> -2
*/
void solve() {
  ll m, n, p;
  cin >> m >> p >> n;
  ll ans = 0;

  ll M = m;
  rep(i,0,n) {
    ll x; cin >> x;
    if (x >= m) ++ans;
    ll diff = fl(x-m,p); // *p/100
    dbg(x,m,m-diff,diff);
    m = M - diff;
  }
  cout << ans << '\n';
}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  solve();
}