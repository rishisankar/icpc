#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define INP(v, n) for (int i=0; i<n; ++i) { cin >> v[i]; }
#define ceil(x) (ll)ceil(x)
#define floor(x) (ll)floor(x)

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

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

template<typename T> inline void print(T obj) { cout << obj << '\n'; }
template<typename T, typename... Args> inline void print(T t, Args... args) { cout << t << " "; print(args...); }

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef vector<int> VI;
typedef vector<int> vi; 
typedef vector<vector<int>> VVI;
typedef vector<long long> VLL;
typedef vector<vector<long long>> VVLL;
typedef vector<bool> VB;
typedef vector<vector<bool>> VVB;
typedef vector<string> VS;
typedef vector<vector<string>> VVS;
typedef pair<int, int> PII;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

VPII dirs{mp(-1,0),mp(1,0),mp(0,-1),mp(0,1)};
const ld pi = 3.1415926535897932384626433832795;
const ll mod = 5318008;


typedef ll T;
ll modpow(T base, T exp, T modulus) {
  base %= modulus;
  T result = 1;
  while (exp > 0) {
    if (exp & 1) result = (result * base) % modulus;
    base = (base * base) % modulus;
    exp >>= 1;
  }
  return result;
}
ll inv(ll x) {
    x%=mod;
    return modpow(x, mod-2, mod);
}


VLL facts(int n, int mod) {
    VLL ans(n+1);
    ans[0] = 1;
    rep(i,1,n+1) {
        ans[i] = ans[i-1] * i;
        ans[i] %= mod;
    }
    return ans;
}

VLL ifacts(int n, VLL& facts) {
    VLL ans(n+1);
    rep(i,0,n+1) {
        ans[i] = inv(facts[i]);
    }
    return ans;
}

VLL F,IF;

void run() {
    int n; cin >> n;
    int x1,y1; int x2,y2;
    cin >> x1 >> y1 >> x2 >> y2;
    int dx = abs(x1-x2);
    int dy = abs(y1-y2);
    if (dy > dx) swap(dx,dy);
    int nd = min(dx,dy);
    int nv = max(dx,dy) - nd;
    dbg(nd,nv);
    // ans = (nd+nv) choose nd
    ll ans = F[nd+nv];
    ans = (ans * IF[nd]) % mod;
    ans = (ans * IF[nv]) % mod;
    print(ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    F = facts(10001,mod);
    IF = ifacts(10001, F);
    ll t; cin >> t;
    // ll t=1;
    rep(tests,0,t) run();
}