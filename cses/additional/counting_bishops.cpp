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
Rotate 45 degrees + process black/white squares independently
For each color, we have some # of rows, each row has some width
Sort the rows by width to get pattern: 1 1 3 3 ... (black), 2 2 4 4 ... (white)
dp[i][j] = # ways to place j pieces in first i (sorted) rows -- note that no col or row can have multiple pieces
    1) don't place piece in ith row ==> dp[i-1][j]
    2) place piece in ith row.
        total ways to do this: width(i) * dp[i-1][j-1]
        but some are invalid. for each of dp[i-1][j-1], there are j-1 cols occupied already
            ==> dp[i-1][j-1] * (j-1) invalid ways
        ==> dp[i-1][j-1] * (width(i) - (j-1))
    Recurrence: dp[i][j] = dp[i-1][j] + dp[i-1][j-1] * (width(i) - (j-1))

note: can place at most 2n-1 bishops (there are only that many diagonals), so don't need to assume k=O(n^2)
*/

VVLL solve(vi& widths, int k) {
    int n = sz(widths);
    VVLL dp(n, VLL(k+1));
    dp[0][0] = 1;
    dp[0][1] = widths[0];
    rep(i,1,n) {
        dp[i][0] = 1;
        rep(j,1,k+1) {
            dp[i][j] = dp[i-1][j] + dp[i-1][j-1] * (widths[i] - j + 1);
            dp[i][j] %= mod;
        }
    }
    return dp;
}

void run() {
    int n,k; cin >> n >> k;
    if (k > 2*n-1) {
        print(0);
        return;
    }
    if (n == 1) {
        // handle separately so we can assume sz(w_w)>0
        print(1);
        return;
    }
    // compute widths by pattern (note that white has 1 fewer row)
    vi b_w, w_w;
    int c = 1;
    rep(i,0,n) {
        b_w.pb(c);
        if (i&1) c+=2;
    }
    c = 2;
    rep(i,0,n-1) {
        w_w.pb(c);
        if (i&1) c+=2;
    }
    VVLL db = solve(b_w,k);
    VVLL dw = solve(w_w,k);
    ll ans = 0;
    rep(i,0,k+1) {
        // i = # of pieces placed on black squares
        ans += db[n-1][i]*dw[n-2][k-i];
        ans %= mod;
    }
    print(ans);
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