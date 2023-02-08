#include <bits/stdc++.h>
using namespace std;

#define FOR(i, j, k) for (int i=j ; i<k ; ++i)
#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define FORI(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k) for (int i=j ; i>=k ; --i)
#define RFORI(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j)
#define RREP(i, j) RFOR(i, j, 0)
#define OREP(i, j) FOR(i, 1, j+1)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
#define F first
#define S second
#define INP(v, n) for (int i=0; i<n; ++i) { cin >> v[i]; }
#define ceil(x) (ll)ceil(x)
#define floor(x) (ll)floor(x)

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

template<typename T> inline void printV(vector<T> &vec) {
    cerr << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        cerr << vec[i] << ' ';
    }
    cerr << '\n';
    cerr << "########\n";
}
template<typename T> inline void printVV(vector<vector<T>> &vec) {
    cerr << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            cerr << vec[i][j] << ' ';
        }
        cerr << '\n';
    }
    cerr << "########\n";
}
template<typename T> inline void print(T obj) { cout << obj << '\n'; }
template<typename T, typename... Args> inline void print(T t, Args... args) { cout << t << " "; print(args...); }
template<typename T> inline void dbg(T obj) { cerr << obj << '\n'; }
template<typename T, typename... Args> inline void dbg(T t, Args... args) { cerr << t << " "; dbg(args...); }

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
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

typedef pair<ll, ll> pll;
const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;

ll gcd(ll a, ll b) {
    if (a == 0) return b; 
    return gcd(b % a, a); 
} 

pll reducefrac(pll x) {
    if (x.F == 0) return {0,1};
    ll g = gcd(x.F, x.S);
    return {x.F/g, x.S/g};
}

pll addfrac(pll x1, pll x2) {
    return reducefrac({x1.F*x2.S+x1.S*x2.F, x1.S*x2.S});
}

void run() {
    int m, n, p;
    cin >> m >> n >> p;
    if (n == 0 && p == 0) {
        print("1/1");
        return;
    }
    else if (p == 0 || n == 0) {
        print("0/1");
        return;
    }
    vector<vector<vector<pll>>> dp(n+10, vector<vector<pll>>(n+10, vector<pll>(p+5, {0,1})));
    // dp[x][y][k] = probability of state (x,y) after pulling k balls.
    dp[n][0][0] = {1,1};
    for (int i = 0; i < p-1; ++i) {
        for (int n0 = 0; n0 <= n; ++n0) {
            for (int n1 = 0; n1 <= n; ++n1) {
                if (n0 + n1 > n) continue; // impossible to be more than n squares
                if (n1 > 0) {
                    // possible to hit a square w 1
                    pll scaled_lik = reducefrac({n1*dp[n0][n1][i].F, (m-i)*dp[n0][n1][i].S});
                    dp[n0][n1-1][i+1] = addfrac(dp[n0][n1-1][i+1], scaled_lik);
                }
                if (n0 > 0) {
                    // possible to hit a square w 0
                    pll scaled_lik = reducefrac({2*n0*dp[n0][n1][i].F, (m-i)*dp[n0][n1][i].S});
                    dp[n0-1][n1+1][i+1] = addfrac(dp[n0-1][n1+1][i+1], scaled_lik);
                }
                if (m-i-2*n0-n1 > 0) {
                    // possible to hit nothing on the board
                    pll scaled_lik = reducefrac({(m-i-2*n0-n1)*dp[n0][n1][i].F, (m-i)*dp[n0][n1][i].S});
                    dp[n0][n1][i+1] = addfrac(dp[n0][n1][i+1], scaled_lik);
                }
            }
        }
    }
    // after p-1 balls, what's the likelihood of there being exactly one square left and hitting it
    int n0 = 1; // need 1 not-crossed square.
    pll res = {0,1};
    for (int n1 = 0; n1 <= n; ++n1) {
        if (n0 + n1 > n) continue; // impossible to be more than n squares
        pll scaled_lik = reducefrac({2*dp[n0][n1][p-1].F, (m-p+1)*dp[n0][n1][p-1].S});
        res = addfrac(res, scaled_lik);
    }
    res = reducefrac(res);
    // REP(i, p) {
    //     dbg("P:",i);
    //     REP(j, n+1) {
    //         REP(k,n+1) {
    //             cout << dp[j][k][i].F << "," << dp[j][k][i].S << "  ";
    //         }
    //         cout << '\n';
    //     }
    //     cout<<'\n';
    // }

    cout << res.F << '/' << res.S << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    // ll t; cin >> t;
    ll t=1;
    REP(tests,t) run();
}