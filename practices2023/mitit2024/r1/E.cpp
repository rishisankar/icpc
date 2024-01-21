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
const ll mod = 1000000007;
// const ll mod = 998244353;

// dist from st --> end in CCW
inline ll distCCW(vector<pll>& locs, ll c, int st, int end) {
    ll sp = locs[st].F;
    ll se = locs[end].F;
    if (se <= sp) se += c;
    return se - sp;
}

// dp[i][j] := CCW interval from i to j inclusive (no center, assumes i & j are already connected)
void p1_precompute(vector<vector<ll>>& dp, vector<pll>& locs, ll c) {
    int n = sz(locs);
    dp.resize(n, VLL(n, LLONG_MAX));
    rep(i,0,n) dp[i][(i+1)%n] = 0; // base
    for (int linv = 2; linv <= n; ++linv) {
        for (int st = 0; st < n; ++st) {
            int end = (st + linv) % n;
            // right most thing conn to start (CAN BE NONE)
            for (int rgmL = st+1; rgmL < st+linv; ++rgmL) {
                int rgm = rgmL % n;
                if (distCCW(locs, c, st, rgm) >= c/2) break;
                ll cst = llabs(locs[st].S-locs[rgm].S) + dp[st][rgm] + dp[rgm][end];
                dp[st][end] = min(dp[st][end], cst);
            }
            // left most conn to end
            for (int lgmL = st+linv-1; lgmL > st; lgmL--) {
                int lgm = lgmL % n;
                if (distCCW(locs, c, lgm, end) >= c/2) break;
                ll cst = llabs(locs[end].S-locs[lgm].S) + dp[st][lgm] + dp[lgm][end];
                dp[st][end] = min(dp[st][end], cst);
            }
            // dbg(st,end,dp[st][end]);
        }
    }
}

// solve specific query
ll solve(VVLL& p1, vector<pll> &locs, ll cen, ll c) {
    // dbg("solve", cen, c);
    int n = sz(locs);
    ll bst = LLONG_MAX;

    // case 1: only one thing connected to the center..
    rep(i,0,n) {
        bst = min(bst, p1[i][i] + llabs(locs[i].S - cen));
    }

    // dbg("with one thing", bst);

    VVLL dp(n, VLL(n, LLONG_MAX)); // dp[i][j] = min cost of connecting interior assuming i, j connected by center alr
    // compute dp...
    rep(i,0,n) dp[i][(i+1)%n] = 0; // base
    for (int linv = 2; linv < n; ++linv) {
        for (int st = 0; st < n; ++st) {
            int end = (st + linv) % n;
            dp[st][end] = p1[st][end]; // if nothing connects to center, equivalent to p1
            // else, something must connect to center
            for (int rgmL = st+1; rgmL < st+linv; ++rgmL) {
                int rgm = rgmL % n;
                ll cst = llabs(cen-locs[rgm].S) + dp[st][rgm] + dp[rgm][end];
                dp[st][end] = min(dp[st][end], cst);
            }
        }
    }

    // ans = over all pairs, pick min dp[i][j] + dp[j][i].
    rep(i,0,n) {
        rep(j,0,n) {
            if (i == j) continue;
            // if (dp[i][j] + dp[j][i] == 2) print(i, j, dp[i][j], dp[j][i]);
            bst = min(bst, dp[i][j] + dp[j][i] + llabs(cen-locs[i].S) + llabs(cen-locs[j].S));
        }
    }

    return bst;
}

void run() {
    int n,q; ll c; cin >>n >> q >> c;
    c*=2;
    vector<pll> inp(n);
    rep(i,0,n) {
        cin >> inp[i].F >> inp[i].S;
        inp[i].F *= 2;
    }
    sort(all(inp));
    vector<ll> queries(q);
    rep(i,0,q) cin >> queries[i];
    VVLL p1; p1_precompute(p1, inp, c);
    // queries.resize(1);
    // dbg(inp);
    // dbg(p1);
    for (ll cen : queries) {
        print(solve(p1, inp, cen, c));
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    ll t; cin >> t;
    // ll t=1;
    rep(tests,0,t) run();
}