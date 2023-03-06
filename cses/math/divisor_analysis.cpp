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
1 + p + .. + p^k = p^{k+1}-1 / p-1

(2^(1+2))^2 * (3^(1))^3
*/

template <typename T>
T modpow(T base, T exp, T modulus) {
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

void run() {
    int n; cin >> n;

    ll ans1 = 1;
    ll ans2 = 1;
    ll ans3 = 1;
    vector<pll> pf(n);

    rep(i,0,n) {
        cin >> pf[i].F >> pf[i].S;
        ans1 = (ans1 * (pf[i].S+1)) % mod;
        ans2 = (ans2 * (modpow(pf[i].F, pf[i].S+1,mod) + mod - 1) ) % mod;
        ans2 = (ans2 * inv(pf[i].F+mod-1)) % mod;
    }

    // compute prod of divisors; (2^(1+2))^2 * (3^(1))^3
    // base is easy
    // exp is # of other choices..
    vector<ll> pre(n+1), suf(n+1);
    pre[0] = suf[0] = 1;
    rep(i,1,n+1) {
        pre[i] = (pre[i-1] * (pf[i-1].S+1)) % (mod-1);
        suf[i] = (suf[i-1] * (pf[n-i].S+1)) % (mod-1);
    }
    rep(i,0,n) {
        ll sm = pf[i].S*(pf[i].S+1)/2; //shouldn't overflow
        ll base = modpow(pf[i].F, sm, mod);
        ll ex = (pre[i] * suf[n-1-i]) % (mod-1);
        ll sc = modpow(base, ex, mod);
        ans3 = (ans3*sc)%mod;
    }

    print(ans1, ans2, ans3);
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