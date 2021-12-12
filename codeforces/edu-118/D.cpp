#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897932384626433832795
#define MOD 998244353 
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

typedef unordered_map<ll, unordered_map<ll, ll>> MLL;

/*
types of sequences:
- max k, no missing - must end in k
- max k, missing k-1 - must end in k-2 or k

(k, 0) - ends in k
(k, 1)  - ends in k-2
(k, 2)  - ends in k

given i:
- dp[i][0] += dp[i][0] + dp[i-1][0]
- dp[i][2] += dp[i][2] + dp[i][1] + dp[i-2][0]
- dp[i+2][1] += dp[i+2][1] + dp[i+2][2]
if i == 0:
  dp[0][0] += 1
if i == 1:
  dp[1][2] += 1


0 2 1:
(0,0) -> 1


*/

ll sm;

ll get(int a, int b, MLL& dp) {
    if (dp.count(a)) {
        if (dp[a].count(b)) {
            return dp[a][b];
        }
    }
    return dp[a][b] = 0;
}

void add (int a, int b, ll val, MLL& dp) {
    get(a,b,dp);
    dp[a][b] += val;
    dp[a][b] %= MOD;
    sm += val;
    sm %= MOD;
}

void run() {
    int n; cin >> n;
    MLL dp;
    VLL v(n);
    INP(v,n);
    sm = 0;
    REP(i, n) {
        add(v[i], 0, get(v[i],0,dp), dp);
        add(v[i], 0, get(v[i]-1,0,dp), dp);
        add(v[i], 2, get(v[i],2,dp), dp);
        add(v[i], 2, get(v[i],1,dp), dp);
        add(v[i], 2, get(v[i]-2,0,dp), dp);
        add(v[i]+2, 1, get(v[i]+2,1,dp), dp);
        add(v[i]+2, 1, get(v[i]+2,2,dp),dp);
        if (v[i] == 0) add(0,0,1,dp);
        if (v[i] == 1) add(1,2,1,dp);
    }
    print(sm);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);
    ll t; cin >> t;
    // ll t=1;
    REP(tests,t) run();
}