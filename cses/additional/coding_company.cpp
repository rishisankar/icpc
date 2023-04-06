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
sort
dp[i][j][k]: # ways to divide the first i coders s.t. there are j open groups and cost so far is k

transition:
dp[i][j][k] = sum{
    1) ith coder is max of a group
        dp[i-1][j+1][k - c[i]]
    2) ith coder is min of a group
        dp[i-1][j-1][k + c[i]]
    3) ith coder is both min/max
        dp[i-1][j][k]
    4) ith coder is inside another group
        dp[i-1][j][k] * j
}

size of table: 100 * 100 * 20000 ==> too big
-> can have at most 50 open groups?
-> don't need to store first dimension (can be size 2)
*/

const int MC = 20005;
vector<VVLL> dp(2,VVLL(51, VLL(MC)));

void run() {
    ll n,x; cin >> n >> x;
    VLL v(n); INP(v,n); sort(all(v));
    dp[0][0][MC/2] = 1;
    int ii,ip;
    rep(i,0,n) {
        ii = i&1;
        ip = ii^1;
        rep(j,0,51) {
            rep(k,0,MC) {
                dp[ip][j][k] = dp[ii][j][k] * (j+1);
                if (j>0 && k+v[i]<MC) dp[ip][j][k] += dp[ii][j-1][k+v[i]];
                if (j<50 && k-v[i]>=0) dp[ip][j][k] += dp[ii][j+1][k-v[i]] * (j+1);
                dp[ip][j][k] %= mod;
            }
        }
    }
    ll ans = 0;
    rep(k,0,MC/2+x+1) {
        ans += dp[ip][0][k];
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