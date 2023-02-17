#include <bits/stdc++.h>
using namespace std;

#define FOR(i, j, k) for (int i=j ; i<k ; ++i)
#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define REP(i, j) FOR(i, 0, j)
#define OREP(i, j) FOR(i, 1, j+1)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
#define F first
#define S second
#define mp make_pair
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

const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	ld dist() const { return sqrt((ld)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	ld angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(ld a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

typedef Point<ld> P;
bool circleInter(P a,P b,ld r1,ld r2,pair<P, P>* out) {
	if (a == b) { assert(r1 != r2); return false; }
	P vec = b - a;
	ld d2 = vec.dist2(), sum = r1+r2, dif = r1-r2,
	       p = (d2 + r1*r1 - r2*r2)/(d2*2), h2 = r1*r1 - p*p*d2;
	if (sum*sum < d2 || dif*dif > d2) return false;
	P mid = a + vec*p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
	*out = {mid + per, mid - per};
	return true;
}

struct circ {
    P center;
    ld r;
    vector<ld> opencuts;
    vector<ld> closecuts;
};

void run() {
    int n; cin >> n;
    vector<pair<int,pii>> inp;
    set<pair<int,pii>> dupcheck;
    REP(i,n) {
        int x,y,r;
        cin >> x >> y >> r;
        inp.PB({r,{x,y}});
    }
    reverse(all(inp));
    vector<circ> circles;
    rep(i,0,n) {
        int r = inp[i].F;
        int x = inp[i].S.F;
        int y = inp[i].S.S;
        if (dupcheck.count(mp(r,mp(x,y)))) continue;
        dupcheck.insert(mp(r,mp(x,y)));
        circ c;
        c.center = P(x,y);
        c.r = r;
        circles.PB(c);
    }
    reverse(all(circles));
    n = circles.size();
    dbg(n);
    rep(i,0,n) {
        dbg(circles[i].center.x,circles[i].center.y,circles[i].r);
    }
    REP(i, n) {
        // draw circle i --> check all prev circles
        rep(j, 0, i) {
            pair<P,P> out;
            bool inter = circleInter(circles[i].center, circles[j].center, circles[i].r, circles[j].r, &out);
            if (!inter || out.F == out.S) {
                // check if circle j fully inside circle i
                P pt1 = P(circles[j].center.x+circles[j].r, circles[j].center.y);
                P pt2 = P(circles[j].center.x-circles[j].r, circles[j].center.y);
                if ((circles[i].center-pt1).dist() <= circles[i].r && (circles[i].center-pt2).dist() <= circles[i].r) {
                    circles[j].opencuts.PB(0);
                    circles[j].closecuts.PB(2*pi);
                }
            } else {
                // two points of intersection --> at least some part is outside...
                ld st = (out.F - circles[j].center).angle();
                ld end = (out.S - circles[j].center).angle();
                if (st < 0) st += 2*pi;
                if (end < 0) end += 2*pi;
                if (st < end) {
                    circles[j].opencuts.PB(st);
                    circles[j].closecuts.PB(end);
                } else {
                    circles[j].opencuts.PB(st);
                    circles[j].closecuts.PB(2*pi);
                    circles[j].opencuts.PB(0);
                    circles[j].closecuts.PB(end);
                }
            }
        }
    }

    REP(i,n) {
        dbg(i, circles[i].opencuts);
        dbg(i, circles[i].closecuts);
    }
    
    ld ans = 0;
    REP(i, n) {
        vector<pair<ld, int>> cuts;
        for (ld x : circles[i].opencuts) cuts.PB({x, 0});
        for (ld x : circles[i].closecuts) cuts.PB({x, 1});
        sort(all(cuts));
        int cutsopen = 0;
        ld prev = 0;
        for (auto p : cuts) {
            if (cutsopen == 0) ans += (p.F-prev) * circles[i].r;
            if (p.S == 0) ++cutsopen;
            else --cutsopen;
            prev = p.F;
        }
        ans += (2*pi-prev)*circles[i].r;
    }
    cout << ans << '\n';
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