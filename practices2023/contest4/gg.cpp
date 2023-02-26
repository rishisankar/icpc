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
#define int ll
const int MOD = 1e9+7;
void solve()
{
  int n, m, k;
  cin >> n >> m >> k;
  int g = n%k;
  int ks = (n-g)/k;
  ll ans = 0;
  rep(i, 0, m) {
    if(ks < 0) break;
    int x = g/m;
    int c = g%m;
    ll dmg = m*(m+1)/2*x + c*(c+1)/2;
    dmg += k*ks*(ks+1)/2+ks*g;
    dbg(g, ks, c, x, dmg);
    ans = max(ans, dmg);
    g += k;
    ks--;
  }
  cout << ans << endl;
}

int32_t main()
{

  solve(); 
}