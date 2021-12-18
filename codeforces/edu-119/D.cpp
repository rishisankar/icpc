#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
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

struct poss {
    int cost;
    unordered_set<ll> sums;

    poss(VLL& vals) {
        cost = vals.size();
        int n = vals.size();
        REP(i, (1 << n)) {
            ll sm = 0;
            REP(j, vals.size()) {
                if (((i >> j) & 1) == 1) {
                    sm += vals[j];
                }
            }
            sums.insert(sm);
        }
    }
};

vector<poss> choices;

// void run() {
//     int n; cin >> n ; VLL vx(n); INP(vx,n);
//     unordered_set<ll> v;
//     bool has1 = false;
//     for (ll g : vx) {
//         v.insert(g);
//         if (g == 1)has1 = true;
//     }
//     VLL cts(3,0);
//     for (ll i : v) {
//         ++cts[i % 3];
//     }
//     bool h1 = false, h2 = false;
//     if (cts[1] > 0) h1 = true;
//     if (cts[2] > 0) h2 = true;

//     ll res = 0;
//     if (h1) ++res; if (h2) ++res;
//     ll thn = 0;
//     for (ll x : v) {
//         if (x % 3 == 0) {
//             ll nd = x/3;
//             if (h1 && h2) --nd;
//             thn = max(thn, nd);
//         } else {
//             ll tmp = x - (x % 3);
//             ll nd = tmp/3;
//             thn = max(thn, nd);
//         }
//     }
//     print(h1,h2,cts[0],cts[1],cts[2]);
//     print(res+thn);
// }

void run() {
    int n; cin >> n ; VLL vx(n); INP(vx,n);
    ll best = LLONG_MAX;
    for (poss p : choices) {
        //dbg("cst", p.cost);
        //for (ll i : p.sums) cerr << i << ' '; cerr << '\n';
        ll ndd = p.cost;
        ll mx3 = 0;
        REP(i, vx.size()) {
            ll fori = LLONG_MAX - 20;
            for (ll j : p.sums) {
                ll d = vx[i] - j;
                if (d < 0) continue;
                if (d % 3 != 0) continue;
                fori = min(fori, d/3);
            }
            mx3 = max(mx3, fori);
        }
        ndd += mx3;
        best = min(best, ndd);
    }
    print(best);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);

    VLL v1 = {};
    VLL v2 = {1};
    VLL v3 = {2};
    VLL v4 = {2,2};
    VLL v5 = {2,1};
    VLL v6 = {2,2,2};
    VLL v7 = {2,1,2};
    VLL v8 = {2,1,1};
    choices.PB(poss(v1));
    choices.PB(poss(v2));
    choices.PB(poss(v3));
    choices.PB(poss(v4));
    choices.PB(poss(v5));
    choices.PB(poss(v6));
    choices.PB(poss(v7));
    choices.PB(poss(v8));

    cout.precision(10);
    ll t; cin >> t;
    // ll t=1;
    REP(tests,t) run();
}