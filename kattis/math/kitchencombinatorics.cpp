#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897932384626433832795
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

void run() {
    int r,s,m,d,n;
    cin >> r >> s >> m >> d >> n;
    vector<ull> ing(r);
    INP(ing,r);
    VVLL st(s);
    VVLL mn(m);
    VVLL dz(d);
    REP(i, s) {
        int k; cin >> k;
        REP(j,k) {
            int in;
            cin >> in;
            --in;
            st[i].PB(in);
        }
    }
    REP(i, m) {
        int k; cin >> k;
        REP(j,k) {
            int in;
            cin >> in;
            --in;
            mn[i].PB(in);
        }
    }
    REP(i, d) {
        int k; cin >> k;
        REP(j,k) {
            int in;
            cin >> in;
            --in;
            dz[i].PB(in);
        }
    }

    VVB pairs(s+m+d+1, VB(s+m+d+1, false));
    REP(i, n) {
        int a, b;
        cin >> a >> b;
        pairs[a][b] = pairs[b][a] = true;
    }

    const ull mod = 1000000000;
    ull tot = 0;
    ull totr = 0;

    REP(i, s) {
        REP(j, m) {
            REP(k, d) {
                int ts = i + 1; int tm = j + 1 + s; int td = k + 1 + s + m;
                if (pairs[ts][tm] || pairs[ts][td] || pairs[tm][td]) continue;
                unordered_set<int> ings;
                for (int l : st[i]) ings.insert(l);
                for (int l : mn[j]) ings.insert(l);
                for (int l : dz[k]) ings.insert(l);
                ull curtot = 0;
                ull curtotr = 1;
                for (int l : ings) {
                    curtot *= ing[l];
                    curtotr *= ing[l];
                    curtot += curtotr/mod;
                    curtotr %= mod;
                    if (curtot > mod || (curtot == mod && curtotr > 0)) {
                        print("too many");
                        exit(0);
                    }
                }
                tot += curtot;
                totr += curtotr;
                tot += totr/mod;
                totr %= mod;
                if (tot > mod || (tot == mod && totr > 0)) {
                    print("too many");
                    exit(0);
                }
            }
        }
    }

    ull res = tot * mod + totr;
    print(res);

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);
    // ll t; cin >> t;
    ll t=1;
    REP(tests,t) run();
}