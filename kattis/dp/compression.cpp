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

bool check(ll y, ll s, ll m) {
    if (s == 0) return y == 0;
    ll ts = 1LL << s;
    ll tsm1 = 1LL << (s-1);
    if (m == 0) {
        return 0 <= y && y < ts;
    } else {
        return -tsm1 <= y && y < tsm1;
    }
}

/*

dp[i][s][m]:
 = cost of compression of v[0..i], assuming v[i] is compressed with s bits and mode m.

# states: N * 30 * 2 (valid)

dp[i][s][m] :=
  dp[i-1][s][m] + s (if possible to add another number in this mode with s bits)
  dp[i-1][best of all s][best of all m] + c + s (if starting a new compression seq and possible to fit)

*/
void run() {
    ll n, c;
    cin >> n >> c;
    VLL v(n);
    INP(v,n);
    vector<vector<vector<ll>>> dp(n, VVLL(31, VLL(2, -1)));

    ll pc = 0;
    REP(i, n) {
        ll npc = LLONG_MAX;
        REP(s, 31) {
            REP(m, 2) {
                int enc = v[i];
                if (m == 1 && i != 0) {
                    // instead, encode diff from prev
                    enc = v[i] - v[i-1];
                }
                // is it possible to encode enc in s bits?
                if (check(enc, s, m)) {
                    dp[i][s][m] = pc + c + s;
                    if (i > 0 && dp[i-1][s][m] != -1) {
                        dp[i][s][m] = min(dp[i][s][m], dp[i-1][s][m] + s);
                    }
                    npc = min(npc, dp[i][s][m]);
                } else {
                    dp[i][s][m] = -1;
                }
            }
        }
        pc = npc;
    }
    print(pc);
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