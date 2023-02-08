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

ll n,s,k;
ll solve(VLL& v) {
    VLL cap(n, s); // stores dist from center to end
    // maximize buckets, l->r
    REP(i, n) {
        if (i == 0) {
            // no left bucket
            cap[i] = min(k, v[i+1]-cap[i+1]-v[i]);
        } else if (i == n-1) {
            // no right bucket
            cap[i] = min(k, v[i]-(v[i-1]+cap[i-1]));
        } else {
            cap[i] = min(k, 
                min(v[i+1]-cap[i+1]-v[i], v[i]-(v[i-1]+cap[i-1])));
        }
    }
    ll sol = 0;
    REP(i, n) {
        sol += cap[i];
    }
    return sol;
}

void run() {
    cin >> n >> s >> k;
    VLL v(n);
    INP(v,n);
    if (n==1) {
        print(k);
        return;
    }
    REP(i,n) { v[i] *= 2; }
    sort(all(v));
    // printV(v);
    VLL cap(n, s); // stores dist from center to end
    // first check if fail already, then return -1
    REP(i, n-1) {
        if (v[i] + cap[i] > v[i+1] - cap[i+1]) {
            print(-1);
            return;
        }
    }
    print(solve(v));
    // VLL v2(n);
    // REP(i, n) {
    //     v2[i] = v[n-1] - v[n-1-i];
    // }
    // // dbg(solve(v2));
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