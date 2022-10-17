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

void run() {
    ll n; cin >> n;
    VLL v(3*n);
    VLL sm(3*n);
    REP(i,3*n) {
        cin >> v[i];
        if (i == 0) sm[i] = v[i]; else sm[i] = v[i] + sm[i-1];
    }

    // value after finishing each stage
    vector<vector<vector<ld>>> dp3(n+5, vector<vector<ld>>(n+5, vector<ld>(n+5, 0)));
    for (int i = 3*n; i >= 0; --i) {
        for (int n3 = 0; n3 <= i/3; ++n3) {
            for (int n2 = 0; n2 <= (i-3*n3)/2; ++n2) {
                for (int n1 = 0; n1 <= (i-3*n3-2*n2); ++n1) {
                    int n0 = i-3*n3-2*n2-n1;
                    // profit state from not throwing the ball
                    if (i == 0) dp3[n3][n2][n1] = 0;
                    dp3[n3][n2][n1] = sm[i-1];
                    ld cp = 0;
                    if (n2 > 0) {
                        cp += n2/(ld)n * dp3[n3+1][n2-1][n1];
                    }
                    if (n1 > 0) {
                        cp += n1/(ld)n * dp3[n3][n2+1][n1-1];
                    }
                    if (n0 > 0) {
                        cp += n0/(ld)n * dp3[n3][n2][n1+1];
                    }
                    if (cp > dp3[n3][n2][n1]) dp3[n3][n2][n1] = cp;
                }
            }
        }
    }

    for (int i = 3*n; i >= 0; --i) {
        for (int n3 = 0; n3 <= i/3; ++n3) {
            for (int n2 = 0; n2 <= (i-3*n3)/2; ++n2) {
                for (int n1 = 0; n1 <= (i-3*n3-2*n2); ++n1) {
                    int n0 = i-3*n3-2*n2-n1;
                    dbg("d",n3,n2,n1,n0, dp3[n3][n2][n1]);
                }
            }
        }
    }


    // expected profit per stage
    vector<vector<vector<ld>>> dp(n/3+5, vector<vector<ld>>(n/2+5, vector<ld>(n+5, 0)));

    for (int i = 1; i <= 3*n; ++i) {
        for (int n3 = 0; n3 <= i/3; ++n3) {
            for (int n2 = 0; n2 <= (i-3*n3)/2; ++n2) {
                for (int n1 = 0; n1 <= (i-3*n3-2*n2); ++n1) {
                    int n0 = i-3*n3-2*n2-n1;
                    
                    ld nwval = 0;
                    if (n0 > 0) {
                        nwval += n0/(ld)n * dp3[n3][n2][n1+1];
                    }
                    if (n1 > 0) {
                        nwval += n0/(ld)n * dp3[n3][n2+1][n1-1];
                    }
                    if (n2 > 0) {
                        nwval += n0/(ld)n * dp3[n3+1][n2-1][n1];
                    }
                    if (nwval < sm[i-1]) continue;
                    
                    // is it worth to throw the ball?
                    ld cp = dp[n3][n2][n1];
                    // ld pfail = n0 / (ld)n;
                    // if (cp > (1-pfail)*(cp+v[i])) continue;

                    // throw the ball, get no profit staying here...
                    dp[n3][n2][n1] = 0;
                    
                    if (n2 > 0) {
                        dp[n3+1][n2-1][n1] += n2/(ld)n * (cp+v[i]);
                    }
                    if (n1 > 0) {
                        dp[n3][n2+1][n1-1] += n1/(ld)n * (cp+v[i]);
                    }
                    dp[n3][n2][n1+1] += n0/(ld)n * (cp+v[i]);
                }
            }
        }
    }
    
    // expected profit at each stage
    // vector<vector<vector<ld>>> dp2(n+5, vector<vector<ld>>(n+5, vector<ld>(n+5, 0)));
    // for (int i = 3*n-1; i >= 0; --i) {
    //     for (int n3 = 0; n3 <= i/3; ++n3) {
    //         for (int n2 = 0; n2 <= (i-3*n3)/2; ++n2) {
    //             for (int n1 = 0; n1 <= (i-3*n3-2*n2); ++n1) {
    //                 // profit state from not throwing the ball
    //                 dp2[n3][n2][n1] = dp[n3][n2][n1];
    //                 if (i != 3*n-1) {
    //                     // consider throwing the ball
    //                     ld bf = 0;
    //                     if (n2 > 0) {
    //                         bf += dp[n3+1][n2-1][n1];
    //                     }
    //                     if (n1 > 0) {
    //                         bf += dp[n3][n2+1][n1-1];
    //                     }
    //                     bf += dp[n3][n2][n1+1];
    //                     dp2[n3][n2][n1] = max(dp[n3][n2][n1], bf);
    //                 }
    //             }
    //         }
    //     }
    // }

    // print(dp2[0][0][0]);

    ld res = 0;
    REP(i, n/3+5) {
        REP(j, n/2+5) {
            REP(k, n+5) {
                res += dp[i][j][k];
            }
        }
    }
    print(res);
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