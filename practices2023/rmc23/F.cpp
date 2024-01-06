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

void run() {
    int n; string s; cin >> n >> s;
    // 0 = empty, 1 = white, 2 = black
    vi state(n);
    rep(i,0,n) {
        if (s[i] == '.') state[i] = 0;
        else if (s[i] == 'W') state[i] = 1;
        else state[i] = 2;
    }
    vector<vector<vector<vector<int>>>> dp(n+5, vector<vector<VI>>(n+5, vector<VI>(3, VI(3)))); // not inclusive
    // 0 = lose, 1 = win (if u r next and state is that)
    rep(i,0,n+1) {
        // base case (empty)
        dp[i][i][1][2] = dp[i][i][2][1] = 1;
    }
    vector<pll> winmoves;
    rep(l,1,n+1) {
        rep(i,0,n) {
            int j = i + l;
            if (j > n) continue;
            rep(lc,0,3) {
                rep(rc,0,3) {
                    // dbg(i,j,lc,rc);
                    unordered_set<int> states;
                    if (state[i] && lc && state[i] != lc) {
                        // move to end
                        states.insert(dp[i+1][j][0][rc]);
                        // move end in
                        states.insert(dp[i+1][j][lc][rc]);
                    }
                    if (state[j-1] && rc && state[j-1] != rc) {
                        // move to end
                        states.insert(dp[i][j-1][lc][0]);
                        // move end in
                        states.insert(dp[i][j-1][lc][rc]);
                    }
                    rep(pt,i,j) {
                        if (pt != j-1) {
                            // can try to move right
                            if (state[pt] && state[pt+1] && state[pt] != state[pt+1]) {
                                int ns = dp[i][pt][lc][0] ^ dp[pt+2][j][state[pt]][rc];
                                states.insert(ns);
                                if (i == 0 && j == n && lc == 0 && rc == 0 && ns == 0) {
                                    winmoves.pb({pt+1, pt+2});
                                }
                            }
                        }
                        if (pt != i) {
                            // can try to move left
                            if (state[pt] && state[pt-1] && state[pt] != state[pt-1]) {
                                int ns = dp[i][pt-1][lc][state[pt]] ^ dp[pt+1][j][0][rc];
                                states.insert(ns);
                                if (i == 0 && j == n && lc == 0 && rc == 0 && ns == 0) {
                                    winmoves.pb({pt+1, pt});
                                }
                            }
                        }
                    }
                    int M;
                    for (M = 0; M < 100000000; ++M) {
                        if (!states.count(M)) {
                            break;
                        }
                    }
                    dp[i][j][lc][rc] = M;
                }
            }
        }
    }
    // dbg(dp[0][n][0][0]);
    sort(all(winmoves));
    print(sz(winmoves));
    for (auto p : winmoves) {
        print(p.F,p.S);
    }
    // dbg(dp[0][9][0][0]);

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