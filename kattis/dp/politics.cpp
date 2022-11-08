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
    int n; cin >> n;
    VVLL v(n, VLL(3));
    vector<ll> pos;
    vector<vector<pair<ll,ll>>> ivs;
    REP(i, n) {
        cin >> v[i][0] >> v[i][1] >> v[i][2];
        if (i == 0 || pos[pos.size()-1] != v[i][0]) {
            pos.PB(v[i][0]);
            vector<pair<ll,ll>> vcs = {{v[i][1], v[i][2]}};
            ivs.PB(vcs);
        } else {
            ivs[ivs.size()-1].PB({v[i][1], v[i][2]});
        }
    }

    int m = pos.size();
    assert(m == ivs.size());

    // dp[i] = expected # hearings assuming free starting at point i
    vector<ld> dp(m);
    // can always listen to the last one
    dp[m-1] = 1;

    for (int i = m-2; i >= 0; --i) {
        ld best = dp[i+1];
        for (pair<ll,ll> p : ivs[i]) {
            ld expt = 1;
            // suppose u take this route...
            for (int j = i+1; j < m; ++j) {
                // left side of iv: either pos[j-1]+1 or pos[i]+p.f
                ld ls = max(pos[i]+p.F, pos[j-1]+1);
                // right side of iv: either pos[j] or pos[i] + p.s
                ld rs = min(pos[j], pos[i]+p.S);
                ld wd = rs-ls+1;
                // dbg(i,j,p.F, p.S, pos[i],pos[j], ls, rs, wd, wd/(p.S-p.F+1));
                if (wd <= 0) wd = 0;
                expt += (dp[j]) * wd / (p.S - p.F + 1);
                // dbg(expt);
            }
            best = max(best ,expt);
        }
        dp[i] = best;
    }

    print(dp[0]);

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