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

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) { x += 0x9e3779b97f4a7c15; x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9; x = (x ^ (x >> 27)) * 0x94d049bb133111eb; return x ^ (x >> 31); }
    size_t operator()(uint64_t x) const { static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count(); return splitmix64(x + FIXED_RANDOM); }
};
template<typename T, typename U> struct safe_map : public std::unordered_map<T,U,custom_hash> {};
template<typename T> struct safe_set : public std::unordered_set<T,custom_hash> {};

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
// const ll mod = 1000000007;
const ll mod = 998244353;

// helper func for matmodpow. assumes both are square matrices
VVLL matmul(VVLL& v1, VVLL& v2, ll mod) {
  int n = v1.size();
  VVLL res(n, VLL(n, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        res[i][j] += v1[i][k]*v2[k][j];
        res[i][j] %= mod;
      }
    }
  }
  return res;
}

// needs to be square matrix
// complexity: O(n^3 log(exp))
VVLL matmodpow(VVLL base, ll exp, ll mod) {
  int n = base.size();
  VVLL result(n,VLL(n,0));
  for(int i=0; i<n;++i)result[i][i]=1;
  while (exp > 0) {
    if (exp & 1) result = matmul(result,base,mod);
    base = matmul(base, base,mod);
    exp >>= 1;
  }
  return result;
}


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
    ll n,L; cin >> n >> L;
    VVLL m(n, VLL(n));
    rep(i,0,n) rep(j,0,n) cin >> m[i][j];
    m[n-1][n-1] = 1;
    rep(i,0,n-1) {
        ll s = 0;
        rep(j,0,n) s += m[i][j];
        rep(j,0,n) {
            m[i][j] *= inv(s);
            m[i][j] %= mod;
        }
    }
    ll goal = 95 * inv(100); goal %= mod;
    VVLL me = matmodpow(m, L, mod);
    rep(T, L, L+10) {
        if (me[0][n-1] == goal) {
            print(T);
            return;
        }
        me = matmul(me, m, mod);
    }
    print(-1);

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