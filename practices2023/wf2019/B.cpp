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

struct custom_hash { // https://codeforces.com/blog/entry/62393
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
typedef vector<pll> VPLL;
VPII dirs{mp(-1,0),mp(1,0),mp(0,-1),mp(0,1)};
const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
// const ll mod = 998244353;

ll n,h,a,b;

const ld eps = 1e-5;

vector<ld> solve(VPLL& pts) {
    vector<ld> furthest(n, 10000000000);
    rep(i,0,n) {
        ld px = pts[i].F, py = pts[i].S;
        rep(j,i+1,n) {
            ld qx = pts[j].F, qy = pts[j].S;
            ld P = qx-px, Q = qy - h;
            ld B = 2*Q-2*P, C = P*P+Q*Q;
            ld res = (-B + sqrt(B*B-4*C))/2;
            furthest[i] = min(furthest[i], res);
        }
        furthest[i] = min(furthest[i], h-py);
    }
    return furthest;
}

vector<ld> solve2(VPLL& pts) {
    vector<ld> furthest(n, 10000000000);
    rep(i,0,n) {
        ld px = pts[i].F, py = pts[i].S;
        rep(j,0,i) {
            ld qx = pts[j].F, qy = pts[j].S;
            ld P = qx-px, Q = qy - h;
            ld B = 2*Q+2*P, C = P*P+Q*Q;
            ld res = (-B + sqrt(B*B-4*C))/2;
            furthest[i] = min(furthest[i], res);
        }
        furthest[i] = min(furthest[i], h-py);
    }
    return furthest;
}


void run() {
    cin >> n >> h >> a >> b;
    VPLL pts(n);
    rep(i,0,n) cin >> pts[i].F >> pts[i].S;
    vector<ld> f1 = solve(pts);
    vector<ld> f2 = solve2(pts);
    dbg(f1);
    dbg(f2);
    VLL dp(n,-1); // dp[i] = min cost assuming last pillar at i
    dp[0] = a * (h-pts[0].S);
    VLL prev(n,-1);
    rep(i,1,n) {
        rep(j,0,i) {
            ld midp = pts[j].F + (pts[i].F-pts[j].F)/2.0L;
            if (j == 5 && i == 6) {
                dbg(pts[j].F,pts[j].S);
                dbg(pts[i].F,pts[i].S);
                dbg(pts[j].F+f1[j], pts[i].F-f2[i], midp);
            }
            if (pts[j].F + f1[j] - midp < -eps || pts[i].F - f2[i] - midp > eps) continue;
            dbg(j,i);
            if (dp[j] == -1) continue;
            ll nc = dp[j] + a*(h-pts[i].S) + b * (pts[i].F - pts[j].F)*(pts[i].F-pts[j].F);
            if (dp[i] == -1 || dp[i] > nc) {
                dp[i] = nc;
                prev[i] = j;
            }
        }
    }
    dbg(dp);
    dbg(prev);
    if (dp[n-1] == -1) print("impossible");
    else print(dp[n-1]);

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