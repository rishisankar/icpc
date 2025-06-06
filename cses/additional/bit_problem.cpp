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

// https://codeforces.com/blog/entry/45223
xi <= 10^6 ==> # bits <= 20

query 1: x | y = x
query 2: x & y = x
query 3: x & y != 0

query 1: 1 --> *, 0 --> 0
query 2: 1 --> 1, 0 --> *


query 1:
- for a bitstring x, consider all subsets ie 1s can become 0s, 0s must stay 0s
   - run SOS over all subsets i of x, A[i] = # of values with value i

query 2: similar but in reverse

query 3:
==> at all pts where x is 1, y = 0
==> by negating x, (~x | y) will give 0 at all points where x is 1 (since y is also 0)
    at points where x was 0, ~x becomes 1 ==> we get 1 at all points where x was 0
    ==> places where x&y == 0 are equivalent to places where ~x | y == ~x

*/

unordered_map<int,int> cts;

const int NB = 20;

pair<VLL,VLL> f1(VLL& v) {
    int n = sz(v);
    VVLL dp((1<<NB), VLL(NB));
    for (auto p : cts) {
        dp[p.F][0] += p.S;
        if (!(p.F&1)) dp[(p.F^1)][0] += p.S;
    }
    for (int i = 0; i < (1 << NB); ++i) {
        rep(k,1,NB) {
            if ((i>>k)&1) dp[i][k] += dp[i ^ (1 << k)][k-1];
            dp[i][k] += dp[i][k-1];
        }
    }
    VLL ans(n);
    rep(i,0,n) {
        ans[i] = dp[v[i]][NB-1];
    }
    VLL ans2(n);
    rep(i,0,n) {
        ans2[i] = n - dp[v[i] ^ ((1 << NB)-1)][NB-1];
    }
    return {ans,ans2};
}

VLL f2(VLL& v) {
    int n = sz(v);
    VVLL dp((1<<NB), VLL(NB));
    for (auto p : cts) {
        dp[p.F][0] += p.S;
        if ((p.F&1)) dp[(p.F^1)][0] += p.S;
    }
    for (int i = (1<<NB)-1; i >= 0; --i) {
        rep(k,1,NB) {
            if (!((i>>k)&1)) dp[i][k] += dp[i ^ (1 << k)][k-1];
            dp[i][k] += dp[i][k-1];
        }
    }
    VLL ans(n);
    rep(i,0,n) {
        ans[i] = dp[v[i]][NB-1];
    }
    return ans;
}

void run() {
    int n; cin >> n;
    VLL v(n); INP(v,n);
    rep(i,0,n) {
        cts[v[i]] ++;
    }
    VLL a1,a3;
    tie(a1,a3) = f1(v);
    VLL a2 = f2(v);
    rep(i,0,n) {
        print(a1[i],a2[i],a3[i]);
    }
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