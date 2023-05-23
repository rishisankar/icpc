#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define INP(v, n) for (int i=0; i<n; ++i) { cin >> v[i]; }
#define ceil(x) (ll)ceil(x)
#define floor(x) (ll)floor(x)

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) 
{ os << '{'; string sep; for (const auto &x: v) os << sep << x, sep = ", "; return os << '}';}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) 
{ return os << '(' << p.first << ", " << p.second << ')'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

template<typename T> inline void print(T obj) { cout << obj << '\n'; }
template<typename T, typename... Args> inline void print(T t, Args... args) { cout << t << " "; print(args...); }

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

VPII dirs{mp(-1,0),mp(1,0),mp(0,-1),mp(0,1)};
const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
// const ll mod = 998244353;
typedef pair<__int128_t,__int128_t> pll;

pll rf(pll x) {
    if (x.S < 0) { x.S *= -1; x.F *= -1; }
    if (x.F == 0 && x.S == 0) return {0,0};
    if (x.F == 0) return {0,1};
    else if (x.S == 0) return {1,0};
    ll g = __gcd(llabs(x.F),llabs(x.S));
    return {x.F/g, x.S/g};
}

pll mf(pll x, pll y) {
    return rf({x.F*y.F, x.S*y.S});
}

pll sf(pll x, pll y) {
    return rf({x.F*y.S-y.F*x.S, x.S*y.S});
}

map<pair<pll,pll>, vector<pair<pll, bool>>> sm;

pair<pll,pll> decomposeLine(pll p1, pll p2) {
    ll dy = p2.S - p1.S;
    ll dx = p2.F - p1.F;
    pll slope = rf({dy,dx});
    pll intercept;
    if (slope.S == 0) intercept = {p1.F,1};
    else {
        // y-mx
        intercept = sf({p1.S,1}, mf(slope, {p1.F,1}));
    }
    return {slope,intercept};
}

void addSeg(pll p1, pll p2) {
    pair<pll,pll> pp = decomposeLine(p1,p2);
    sm[pp].push_back({p1,0});
    sm[pp].push_back({p2,1});
}

void readTriangles(bool flip) {
    int n; cin >> n;
    rep(i,0,n) {
        ll x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        vector<pll> pts;
        pts.pb({x1,y1});
        pts.pb({x2,y2});
        pts.pb({x3,y3});
        ll dx1 = x2-x1, dy1 = y2-y1, dx2 = x3-x2, dy2 = y3-y2;
        ll cross = dx1 * dy2 - dy1 * dx2;
        if (cross < 0) reverse(all(pts));
        if (flip)reverse(all(pts));
        rep(j,0,3) addSeg(pts[j], pts[(j+1)%3]);
    }
}

void run() {
    readTriangles(0); readTriangles(1);
    for (auto& p : sm) {
        sort(all(p.S));
        int ct = 0;
        bool start = 0;
        pll prev;
        for (auto& pt : p.S) {
            if (start && ct != 0 && prev != pt.F) {
                print("no");
                return;
            }
            prev = pt.F;
            start = 1;
            ct += (pt.S ? 1 : -1);
        }
    }
    print("yes");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    // ll t; cin >> t;
    ll t=1;
    rep(tests,0,t) run();
}