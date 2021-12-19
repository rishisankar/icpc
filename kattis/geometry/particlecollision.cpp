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

typedef pair<ld,ld> pt;

const ld VL = 0.0005;
const int thresh = 200;
ld r;

bool oob(pt p) {
    return (p.first > 1000+thresh || p.second > 1000+thresh || p.first < -1000 - thresh || p.second < -1000 - thresh);
}

ld ptdist(pt p1, pt p2) {
    ld dx = p1.first - p2.first;
    ld dy = p1.second - p2.second;
    return sqrt(dx*dx + dy*dy);
}

int testIntersection(pt p1, vector<pt>& others, ld& xv, ld& yv) {

    ld veclen = sqrt(xv*xv+yv*yv);
    xv = xv * VL / veclen;
    yv = yv * VL / veclen;
    // dbg("vel",xv,yv);

    while (!oob(p1)) {
        for (int i = 0; i < others.size(); ++i) {
            pt oth = others[i];
            ld dist = ptdist(p1, oth);
            if (dist <= 2*r) {
                // dbg("intersection", p1.first,p1.second, oth.first, oth.second);
                xv = oth.first - p1.first;
                yv = oth.second - p1.second;
                return i;
            }
        }

        p1.first += xv;
        p1.second += yv;
    }
    return -1;
}

void run() {
    // int n; cin >> n ; VLL v(n); INP(v,n);
    pair<ld,ld> p1,p2,p3;
    cin >> p1.first >> p1.second >> p2.first >> p2.second >> p3.first >> p3.second;
    ld xv,yv; cin >> xv >> yv;
    cin >> r;

    vector<pt> others = {p2,p3};
    int int1 = testIntersection(p1, others, xv, yv);
    // dbg("i1",int1, xv, yv);
    if (int1 == -1) {
        print(5);
        return;
    }

    vector<pt> others2;
    pt curpt;
    if (int1 == 0) {
        curpt = p2;
        others2.PB(p3);
    } else {
        curpt = p3;
        others2.PB(p2);
    }

    int int2 = testIntersection(curpt, others2, xv, yv);
    // dbg("i2",int2);
    if (int2 == -1) {
        if (int1 == 0) {
            print(3);
            return;
        } else {
            print(4);
            return;
        }
    } else {
        if (int1 == 0) {
            print(1);
            return;
        } else {
            print(2);
            return;
        }
    }

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