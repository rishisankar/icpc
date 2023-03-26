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

// https://oeis.org/A002464

// inline bool btf(vi& v) {
//     for (int i = 1; i < sz(v); ++i) {
//         if (abs(v[i]-v[i-1]) == 1) return false;
//     }
//     return true;
// }

// void run() {
//     int n; cin >> n;
//     vi v(n);
//     rep(i,0,n) v[i] = i+1;
//     int ct = 0;
//     do {
//         if (btf(v))++ct;
//     } while (next_permutation(all(v)));
//     print(ct);
// }

/*
or dp in n^2: dp[i][j][k] = permutations with length i, j pairs of adj #s so far not including (i,i+1), k=1=>i adj to i-1, k=0=> not
(untested but smth like this should work)
cases:
- insert i+1 next to i:
    - dp[i+1][j][1] += 2 * dp[i][j][0]
    - dp[i+1][j][1] += dp[i][j][1] + dp[i][j-1][1]  (depends on if you put btwn i,i-1 pairing)
- insert i+1 btwn numbers that have difference 1 but aren't (i,i+1)
    - dp[i+1][j][0] += (j+1) * dp[i][j+1][0]
    etc
- neither of above:
    - dp[i+1][j][0] += (n-j-1) * dp[i][j][0] // idk

*/

void run() {
    int n; cin >> n;
    VLL dp(n+1);
    dp[0] = dp[1] = 1;
    dp[2] = dp[3] = 0;
    rep(i,4,n+1) {
        dp[i] = ((i+1)*dp[i-1]) % mod - ((i-2)*dp[i-2] % mod) - ((i-5)*dp[i-3] % mod) + ((i-3)*dp[i-4])%mod;
        dp[i] = ((dp[i]%mod)+mod)%mod;
    }
    print(dp[n]);
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