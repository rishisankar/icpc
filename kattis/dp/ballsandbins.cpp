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

const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;

/*
dp[n3][n2][n1] = expected profit when you have thrown n3*3+n2*2+n1 balls and ended at cur stage


dp[n3][n2][n1] = max(
    1) don't throw any more balls
        profit = sm[total # balls so far]
    2) throw more balls
        profit = n3/n * 0 + n2/n * dp[n3+1][n2-1][n1] + n1/n * dp[n3][n2+1][n1-1] + n0/n * dp[n3][n2+1][n1-1]
)
*/

void run() {
    ll n; cin >> n;
    VLL v(3*n);
    VLL sm(3*n);
    REP(i,3*n) {
        cin >> v[i];
        if (i == 0) sm[i] = v[i]; else sm[i] = v[i] + sm[i-1];
    }

    vector<vector<vector<ld>>> dp(n+5, vector<vector<ld>>(n+5, vector<ld>(n+5, 0)));
    for (int i = 3*n; i >= 0; --i) { // i = # balls thrown
        for (int n3 = 0; n3 <= i/3; ++n3) {
            for (int n2 = 0; n2 <= (i-3*n3)/2; ++n2) {
                int n1 = i - 3*n3 - 2*n2;
                int n0 = n-n3-n2-n1;
                if (n3 < 0 || n2 < 0 || n1 < 0 || n0 < 0) {
                    continue;
                }
                if (i == 3*n) {
                    // can't throw more balls -> profit based on sum
                    dp[n3][n2][n1] = sm[i-1];
                } else {
                    // profit if you don't throw any more balls
                    ld pf1 = i == 0 ? 0 : sm[i-1];

                    // if u do...
                    ld pf2 = 0;
                    if (n2 > 0) pf2 += n2/(ld)n * dp[n3+1][n2-1][n1];
                    if (n1 > 0) pf2 += n1/(ld)n * dp[n3][n2+1][n1-1];
                    if (n0 > 0) pf2 += n0/(ld)n * dp[n3][n2][n1+ 1];
                    dp[n3][n2][n1] = max(pf1, pf2);
                }
            }
        }
    }

    print(dp[0][0][0]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    cout.setf(ios::fixed);
    cout.precision(15);
    // ll t; cin >> t;
    ll t=1;
    REP(tests,t) run();
}