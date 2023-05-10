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

Visualize problem as a full binary search tree of height 61
- at depth d (starting with d=0), u have interval size 1e18/2^d
Need to be at d=60 at least
*/

const int G = 419;  // number of BS guesses
const ld P = 1/13.L; // probability of lie
const ld PB = 1-(1-P)*(1-P); // probability of backtracking up incorrectly
const ld PC = 1-P*P; // probability of backtracking up correctly (check?)

void run() {
    dbg(P,PB,PC);
    // dp[i][j][k] = After i guesses, probability of being at correct depth j, with additional incorrect depth k
    vector<vector<vector<ld>>> dp(G+1, vector<vector<ld>>(G+1, vector<ld>(G+1)));
    dp[0][0][0] = 1;
    rep(g,0,G-2) {
        rep(d,0,g+1) {
            rep(di,0,g+1) {
                if (di == 0) {
                    if (d != 0) {
                        dp[g+2][d-1][di] += PB * dp[g][d][di];
                        if (d < 60) {
                            // query made, chance of incorrect
                            dp[g+3][d+1][di] += (1-PB) * (1-P) * dp[g][d][di];
                            dp[g+3][d][di+1] += (1-PB) * P * dp[g][d][di];
                        } else {
                            // no query made, just go down
                            dp[g+2][d+1][di] += (1-PB) * dp[g][d][di];
                        }
                    } else { // d,di == 0
                        // no backtrack query made
                        dp[g+1][d+1][di] += (1-P) * dp[g][d][di];
                        dp[g+1][d][di+1] += P * dp[g][d][di];
                    }
                } else { // di > 0
                    dp[g+2][d][di-1] += PC * dp[g][d][di];
                    dp[g+3][d][di+1] += (1-PC) * dp[g][d][di];
                }
            }
        }
    }
    // you win if your correct depth is at least 60
    ld pwin = 0;
    rep(g,G-2,G+1) {
        rep(d,60,G+1) {
            rep(di,0,G+1) {
                pwin += dp[g][d][di];
            }
        }
    }
    print("Probability of winning a game:", pwin);

    // next: you get a testcase if you get 248/250 cases
    ld ptest = 0;
    VLL nck{31125, 250, 1};
    for (int i = 248; i <= 250; ++i) {
        ptest += powl(pwin, i) * powl(1-pwin,250-i) * nck[i-248];
    }
    print("Probability of getting a testcase:", ptest);

    print("Probability of getting 30 testcases:", powl(ptest, 30));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    cout.setf(ios::fixed);
    cout.precision(30);
    // ll t; cin >> t;
    ll t=1;
    rep(tests,0,t) run();
}