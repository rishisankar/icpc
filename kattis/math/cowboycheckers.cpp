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

struct dm {
    VPII pts;
    VPII missing;
};

bool test(dm& d, vector<vector<char>>& vx) {
    int cw = 0;
    int ce = 0;
    for (PII pt : d.pts) {
        if (vx[pt.S][pt.F] == 'W') ++cw;
    }
    for (PII pt : d.missing) {
        if (vx[pt.S][pt.F] == '.') ++ce;
    }
    return cw == 5 && ce == 1;
}

void run() {
    vector<dm> ds;
    dm d1;
    d1.pts = {{0,0}, {3,0}, {6,0}, {1,1}, {3,1}, {5,1}};
    d1.missing = {{3,0}, {3,1}};
    ds.PB(d1);
    dm d2;
    d2.pts = {{0,0}, {3,0}, {6,0}, {0,3}, {1,3}, {2,3}};
    d2.missing = {{0,0}, {0,3}};
    ds.PB(d2);
    dm d3;
    d3.pts = {{0,0}, {3,0}, {6,0}, {4,3}, {5,3}, {6,3}};
    d3.missing = {{6,0}, {6,3}};
    ds.PB(d3);
    dm d4;
    d4.pts = {{1,1}, {3,1}, {5,1}, {0,3}, {1,3}, {2,3}};
    d4.missing = {{1,1}, {1,3}};
    ds.PB(d4);
    dm d5;
    d5.pts = {{1,1}, {3,1}, {5,1}, {4,3}, {5,3}, {6,3}};
    d5.missing = {{5,1}, {5,3}};
    ds.PB(d5);
    dm d6;
    d6.pts = {{1,1}, {3,1}, {5,1}, {2,2}, {3,2}, {4,2}};
    d6.missing = {{3,1}, {3,2}};
    ds.PB(d6);
    dm d7;
    d7.pts = {{2,2}, {3,2}, {4,2}, {0,3}, {1,3}, {2,3}};
    d7.missing = {{2,2}, {2,3}};
    ds.PB(d7);
    dm d8;
    d8.pts = {{2,2}, {3,2}, {4,2}, {4,3}, {5,3}, {6,3}};
    d8.missing = {{4,2}, {4,3}};
    ds.PB(d8);

    vector<vector<char>> v(7, vector<char>(7));
    vector<vector<char>> vh(7, vector<char>(7));
    vector<vector<char>> vt(7, vector<char>(7));
    vector<vector<char>> vth(7, vector<char>(7));
    REP(i, 7) {
        REP(j, 7) {
            cin >> v[i][j];
            vt[j][i] = v[i][j];
        }
    }
    REP(i, 7) {
        REP(j, 7) {
            vh[6-i][j] = v[i][j];
            vth[6-i][j] = vt[i][j];
        }
    }

    vector<vector<vector<char>>> vs = {v,vh,vt,vth};

    for (dm d : ds) {
        for (vector<vector<char>> vx : vs) {
            if (test(d,vx)) {
                print("double mill");
                return;
            }
        }
    }
    print("no double mill");
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