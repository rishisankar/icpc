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
const ll mod = 1000000007;
// const ll mod = 998244353;

/*

dp state: how many ways to clear some subarray
dp[i][j] =
    iterate over all pairs for first letter



aSaT

p removals in T
q removals in S

[(p+q) choose p] * s(T) * s(S)

*/

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

VVLL dp;
string s;
int n;
VLL F,IF;

ll solve(int l, int r) {
    if (r<l) return 1;
    if ((r-l+1)&1) return 0;
    if (dp[l][r] != -1) return dp[l][r];
    ll ans = 0;
    for (int i = l+1; i <= r; i+=2) {
        if (s[l] == s[i]) {
            ll L1 = (i-1-(l+1)+1)/2+1;
            ll L2 = (r-(i+1)+1)/2;
            // L1 + L2 choose L1
            ll sm = ((F[L1+L2] * IF[L1])%mod * IF[L2])%mod;
            ans += (solve(l+1, i-1)*solve(i+1,r))%mod*sm;
            ans %= mod;
        }
    }
    return dp[l][r] = ans;
}

void run() {
    F = facts(100000,mod);
    IF = ifacts(100000, F);
    cin >> s;
    n = sz(s);
    dp.assign(n, VLL(n,-1));
    print(solve(0,n-1));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    // ll t; cin >> t;
    ll t=1;
    rep(tests,0,t) run();
}