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

struct parabola {
    ld a, b;
    parabola(ld a0, ld b0) : a(a0), b(b0) {}
    pair<ld,ld> gete() {
        ld v = sqrt(b);
        return {-v+a,v+a};
    }
    ld area(ld l, ld r) {
        //-1/3 (x-a)^3 + bx
        ld a1 = -1/3.0*(r-a)*(r-a)*(r-a) + b*r;
        ld a2 = -1/3.0*(l-a)*(l-a)*(l-a) + b*l;
        return a1-a2;
    }
};
// -(x-3)^2+5  -> integral = -1/3(x-3)^3 + 5x
// -(x-4)^2+4
void run() {
    int n; cin >> n;
    vector<parabola> eqns;
    REP(i, n) {
        int a,b; cin >> a >> b;
        if (b <= 0) continue;
        parabola p(a,b);
        eqns.PB(p);
    }
    n = eqns.size();
    vector<pair<ld, int>> pts;
    REP(i,n) {
        pair<ld,ld> edpt = eqns[i].gete();
        pts.PB({edpt.F, i});
        pts.PB({edpt.S, i});
    }
    sort(all(pts));
    unordered_set<int> open;
    vector<vector<ld>> ints(n);
    for (int i = 0; i < pts.size(); ++i) {
        if (open.count(pts[i].S)) {
            open.erase(pts[i].S);
            if (open.size() >= 1) {
                ints[pts[i].S].PB(pts[i].F);
            }
            if (open.size() < 2) {
                for (int x : open) {
                    ints[x].PB(pts[i].F);
                }
            }
        } else {
            open.insert(pts[i].S);
            if (open.size() == 2) {
                for (int x : open) {
                    ints[x].PB(pts[i].F);
                }
            } else if (open.size() > 2) {
                ints[pts[i].S].PB(pts[i].F);
            }
        }
    }
    ld res = 0;
    REP(i, n) {
        REP(j, ints[i].size()/2) {
            res += eqns[i].area(ints[i][2*j], ints[i][2*j+1]);
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