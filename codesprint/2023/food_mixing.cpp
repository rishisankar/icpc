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
typedef pair<long long, long long> pll;
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

VPII dirs{mp(-1,0),mp(1,0),mp(0,-1),mp(0,1)};
const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
// const ll mod = 998244353;

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
	ld dist() const { return sqrtl((ld)dist2()); }
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

typedef Point<ll> P;
vector<P> convexHull(vector<P> pts) {
	if (sz(pts) <= 1) return pts;
	sort(all(pts));
	vector<P> h(sz(pts)+1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(all(pts)))
		for (P p : pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

template<class P>
int sideOf(const P& s, const P& e, const P& p, ld eps) {
	auto a = (e-s).cross(p-s);
	ld l = (e-s).dist()*eps;
	return (a > l) - (a < -l);
}

bool inHull(const vector<P>& l, P p, bool strict = true) {
	int a = 1, b = sz(l) - 1, r = !strict;
	if (sz(l) < 3) return r && onSegment(l[0], l.back(), p);
	if (sideOf(l[0], l[a], l[b]) > 0) swap(a, b);
	if (sideOf(l[0], l[a], p) >= r || sideOf(l[0], l[b], p)<= -r)
		return false;
	while (abs(a - b) > 1) {
		int c = (a + b) / 2;
		(sideOf(l[0], l[c], p) > 0 ? b : a) = c;
	}
	return sgn(l[a].cross(l[b], p)) < r;
}

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (d == 0) // if parallel
		return {-(s1.cross(e1, s2) == 0), P(0, 0)};
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
}

template<class P>
ld find_px(P p1, P p2, P z) {
    dbg(p1.x,p2.x,z.x,((z.x - p1.x) / (ld)(p2.x - p1.x)));
    ld ans;
    if (p1.x == p2.x) {
        ans = (z.y - p2.y) / (ld)(p1.y - p2.y);
    } else {
        ans = (z.x - p2.x) / (ld)(p1.x - p2.x);
    }
    if (ans < 0) {
        dbg(p1.x,p1.y);
        dbg(p2.x,p2.y);
        dbg(z.x,z.y);
        dbg(ans);
    }
    return ans;
}

void printAns(vector<ld>& props, VLL& r) {
    dbg(props);
    int n = sz(props);
    vector<ld> ans(n);
    ll sm = 0;
    rep(i,0,n) sm += r[i];
    rep(i,0,n) {
        ans[i] += (r[i] / (ld)100);
        ans[i] += props[i] / 100.L * (100-sm);
    }
    print("Yes");
    for (ld l : ans) cout << setprecision(20) << l << ' ';
    cout << '\n';
}

void solveSeg(P p1, P p2, P gl, vector<ld>& props, VLL& r, map<pll, int>& nm) {
    int x = nm[{p1.x, p1.y}], y = nm[{p2.x, p2.y}];
    props[x] = find_px(p1,p2,gl);
    props[y] = 1 - props[x];
    printAns(props, r);
}

void run() {
    int n; cin >> n;
    VLL a(n), b(n), r(n);
    INP(a,n); INP(b,n); INP(r,n);
    ll x,y; cin >> x >> y;
    ll sr = 0;
    rep(i,0,n) sr += r[i];
    if (sr == 100) {
        ll sx = 0, sy = 0;
        rep(i,0,n) {
            sx += r[i]*a[i];
            sy += r[i]*b[i];
        }
        if (sx == x*100 && sy == y*100) {
            print("Yes");
            rep(i,0,n) cout << setprecision(20) << (r[i]/(ld)100) << ' ';
            cout << '\n';
        } else {
            print("No");
        }
        return;
    }
    x*=100; y*=100;
    vector<P> origPts;
    ll glx = 0, gly = 0;
    rep(i,0,n) {
        glx += r[i] * a[i];
        gly += r[i] * b[i];
    }
    rep(i,0,n) {
        a[i] *= (100-sr);
        b[i] *= (100-sr);
    }
    rep(i,0,n) origPts.emplace_back(a[i],b[i]);
    vector<P> hull = convexHull(origPts);
    map<pll, int> nm;
    rep(i,0,n) nm[{a[i], b[i]}] = i;
    ll nx = x - glx;
    ll ny = y - gly;
    P gl(nx,ny);
    dbg(nx,ny);
    vector<ld> props(n);
    int sh = sz(hull);
    if (sh == 1) {
        if (hull[0] == gl) {
            int x = nm[{hull[0].x, hull[0].y}];
            props[x] = 1;
            printAns(props, r);
        } else {
            print("No");
        }
        return;
    } else if (sh == 2) {
        if (onSegment(hull[0], hull[1], gl)) {
            solveSeg(hull[0], hull[1], gl, props, r, nm);
        } else {
            print("No");
        }
        return;
    }
    if (!inHull(hull, gl, false)) {
        print("No");
        return;
    }
    rep(i,1,sh-1) {
        vector<P> tri{hull[0], hull[i], hull[i+1]};
        if (inHull(hull, gl, false)) {
            // solve within hull
            vi is{nm[{hull[0].x, hull[0].y}], nm[{hull[i].x, hull[i].y}], nm[{hull[i+1].x, hull[i+1].y}]};
            ld scl = 100000000.L;
            Point<ld> p1(hull[0].x/scl,hull[0].y/scl), p2(hull[i].x/scl,hull[i].y/scl), p3(hull[i+1].x/scl, hull[i+1].y/scl), gp(nx/scl,ny/scl);
            rep(x,0,3) {
                if (onSegment(tri[x], tri[(x+1)%3], gl)) {
                    return solveSeg(tri[x], tri[(x+1)%3], gl, props, r, nm);
                }
            }
            pair<int,Point<ld>> insc = lineInter(p1,p2,p3,gp);
            assert(insc.F == 1);
            rep(i,0,3) dbg(tri[i].x,tri[i].y);
            dbg(insc.S.x, insc.S.y);
            ld prop1 = find_px(p1,p2,insc.S);
            assert(prop1 >= 0);
            ld prop3 = find_px(p3,insc.S,gp);
            assert(prop3 >= 0);
            dbg(prop1, prop3);
            props[is[2]] = prop3;
            props[is[0]] = prop1 * (1-prop3);
            props[is[1]] = (1-prop1) * (1-prop3);
            printAns(props, r);
            return;
        }
    }
    assert(false); // should never get here
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