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

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) { x += 0x9e3779b97f4a7c15; x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9; x = (x ^ (x >> 27)) * 0x94d049bb133111eb; return x ^ (x >> 31); }
    size_t operator()(uint64_t x) const { static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count(); return splitmix64(x + FIXED_RANDOM); }
};
template<typename T, typename U> struct safe_map : public std::unordered_map<T,U,custom_hash> {};
template<typename T> struct safe_set : public std::unordered_set<T,custom_hash> {};

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

void sleep(int microseconds) {
    int ct = 0;
    for (int i = 0; i < microseconds; ++i) {
        for (int j = 0; j < 2899; ++j) {
            if (ct == 313635) cout << ' ';
            ct++;
        }
    }
}

void inf() {
    print("infinitely many");
}

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
    __int128_t bcross(P p) const { return x * (__int128_t)p.y - y*(__int128_t)p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    __int128_t bcross(P a, P b) const { return (a-*this).bcross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

typedef Point<ll> P;
typedef Point<ld> Q;

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

pair<int, Q> lineInter(Q s1, Q e1, Q s2, Q e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (d == 0) // if parallel
		return {-(s1.cross(e1, s2) == 0), Q(0, 0)};
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
}

int sideOf(P s, P e, P p) { 
    return sgn(s.bcross(e, p)); 
}

template<class T>
T polygonArea2(vector<Point<T>>& v) {
	T a = v.back().cross(v[0]);
	rep(i,0,sz(v)-1) a += v[i].cross(v[i+1]);
	return a;
}

/// extend in direction of s1, see how many pts; second is last pt (-1 if no last pt)
pair<ll,P> latpts(P s1, P f1, P s2, P f2) {
    ll dx = s1.x - f1.x;
    ll dy = s1.y - f1.y;
    ll g = __gcd(llabs(dx),llabs(dy));
    dx/=g;
    dy/=g;
    ll mx = 1000000000000LL;
    ll lo = 0, hi = mx, bst = 0;
    int gg = sideOf(s2,f2,s1);
    while (lo <= hi) {
        ll mid = (lo + hi)/2;
        ll px = s1.x + dx * mid;
        ll py = s1.y + dy * mid;
        P p(px,py);
        int ss = sideOf(s2,f2,p);
        if (ss == 0) {
            return {mid, p};
        }
        else if (ss == gg) {
            bst = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    if (bst == mx) return {-1,s1};
    else return {bst, P(s1.x + dx * bst, s1.y + dy * bst)};
}

/// # lattice points on segment from s to f (inclusive)
ll acps(P s, P f) {
    ll dx = f.x - s.x;
    ll dy = f.y - s.y;
    ll g = __gcd(llabs(dx),llabs(dy));
    return g + 1;
}

void run() {
    int n; cin >> n;
    vector<P> origPts;
    rep(i,0,n) {
        ll x,y; cin >> x >> y;
        origPts.emplace_back(x,y);
    }
    vector<P> hull = convexHull(origPts);
    n = sz(hull);

    vector<Q> dhull;
    rep(i,0,n) {
        dhull.emplace_back(hull[i].x, hull[i].y);
    }

    ll ans = 0;
    rep(i,0,n) {
        P s1 = hull[(i+1)%n];
        P f1 = hull[(i+2)%n];
        P s2 = hull[i];
        P f2 = hull[(i+n-1)%n];

        auto l1 = latpts(s1,f1,s2,f2);
        auto l2 = latpts(s2,f2,s1,f1);
        if (l1.F == -1 || l2.F == -1) return inf();

        P i1 = l1.S, i2 = l2.S;

        if (i1 == i2) {
            // triangle with integer coords!
            dbg("case 1");
            vector<P> tripts{s1,s2,i1};
            ll area2 = llabs(polygonArea2(tripts));
            ll bpts = l1.F + l2.F - 1 + acps(s1,s2);
            ll ipts = (area2 - bpts + 2) / 2;
            assert((area2-bpts) % 2 == 0);
            ans += ipts;
        } else if (l1.F > 0 && l2.F > 0) {
            // bounding box hack?
            dbg("case 2");
            vector<P> tripts{s1,s2,i2,i1};
            ll area2 = llabs(polygonArea2(tripts));
            ll bpts = l1.F + l2.F - 2 + acps(s1,s2) + acps(i1,i2);
            ll ipts = (area2 - bpts + 2) / 2;
            assert((area2-bpts) % 2 == 0);
            ipts += (acps(i1,i2) - 2);

            // now need to compute in small triangle
            Q ds1 = dhull[(i+1)%n];
            Q df1 = dhull[(i+2)%n];
            Q ds2 = dhull[i];
            Q df2 = dhull[(i+n-1)%n];
            pair<int, Q> inter = lineInter(ds1, df1, ds2, df2);
            // if (inter.F != 1) return inf();
            assert(inter.F == 1);
            Q ip = inter.S;
            ll xmin = min(min((ll)ip.x, i1.x), i2.x) - 1000;
            ll xmax = max(max((ll)ip.x, i1.x), i2.x) + 1000;
            ll ymin = min(min((ll)ip.y, i1.y), i2.y) - 1000;
            ll ymax = max(max((ll)ip.y, i1.y), i2.y) + 1000;

            int SO1 = sideOf(s1,f1,i2);
            int SO2 = sideOf(s2,f2,i1);
            int SO3 = sideOf(i1,i2,f2) * (-1);
            assert(SO1 != 0);
            assert(SO2 != 0);
            assert(SO3 != 0);

            for (ll xp = xmin; xp <= xmax; ++xp) {
                for (ll yp = ymin; yp <= ymax; ++yp) {
                    P cpt(xp,yp);
                    int SOP1 = sideOf(s1,f1,cpt);
                    if (SOP1 != SO1) continue;
                    int SOP2 = sideOf(s2,f2,cpt);
                    if (SOP2 != SO2) continue;
                    int SOP3 = sideOf(i1,i2,cpt);
                    if (SOP3 != SO3) continue;
                    ++ipts;
                }
            }
            ans += ipts;
        } else if (l1.F == 0 && l2.F == 0) {

            // now need to compute in small triangle
            Q ds1 = dhull[(i+1)%n];
            Q df1 = dhull[(i+2)%n];
            Q ds2 = dhull[i];
            Q df2 = dhull[(i+n-1)%n];
            pair<int, Q> inter = lineInter(ds1, df1, ds2, df2);
            // if (inter.F != 1) return inf();
            assert(inter.F == 1);
            Q ip = inter.S;
            ll xmin = min(min((ll)ip.x, i1.x), i2.x) - 1000;
            ll xmax = max(max((ll)ip.x, i1.x), i2.x) + 1000;
            ll ymin = min(min((ll)ip.y, i1.y), i2.y) - 1000;
            ll ymax = max(max((ll)ip.y, i1.y), i2.y) + 1000;

            int SO1 = sideOf(s1,f1,i2);
            int SO2 = sideOf(s2,f2,i1);
            int SO3 = sideOf(i1,i2,f2) * (-1);
            assert(SO1 != 0);
            assert(SO2 != 0);
            assert(SO3 != 0);

            ll ipts = 0;
            for (ll xp = xmin; xp <= xmax; ++xp) {
                for (ll yp = ymin; yp <= ymax; ++yp) {
                    P cpt(xp,yp);
                    int SOP1 = sideOf(s1,f1,cpt);
                    if (SOP1 != SO1) continue;
                    int SOP2 = sideOf(s2,f2,cpt);
                    if (SOP2 != SO2) continue;
                    int SOP3 = sideOf(i1,i2,cpt);
                    if (SOP3 != SO3) continue;
                    ++ipts;
                }
            }
            ans += ipts;

        } else if (l2.F == 0) {
            vector<P> tripts{s1,s2,i1};
            ll area2 = llabs(polygonArea2(tripts));
            ll bpts = acps(s1,s2) + acps(s2,i1) + acps(s1,i1) - 3;
            ll ipts = (area2 - bpts + 2) / 2;
            ipts += (acps(i1,s2) - 2);

            // now need to compute in small triangle
            Q ds1 = dhull[(i+1)%n];
            Q df1 = dhull[(i+2)%n];
            Q ds2 = dhull[i];
            Q df2 = dhull[(i+n-1)%n];
            pair<int, Q> inter = lineInter(ds1, df1, ds2, df2);
            // if (inter.F != 1) return inf();
            assert(inter.F == 1);
            Q ip = inter.S;
            ll xmin = min(min((ll)ip.x, i1.x), i2.x) - 1000;
            ll xmax = max(max((ll)ip.x, i1.x), i2.x) + 1000;
            ll ymin = min(min((ll)ip.y, i1.y), i2.y) - 1000;
            ll ymax = max(max((ll)ip.y, i1.y), i2.y) + 1000;

            int SO1 = sideOf(s1,f1,i2);
            int SO2 = sideOf(s2,f2,i1);
            int SO3 = sideOf(i1,i2,f2) * (-1);
            assert(SO1 != 0);
            assert(SO2 != 0);
            assert(SO3 != 0);

            for (ll xp = xmin; xp <= xmax; ++xp) {
                for (ll yp = ymin; yp <= ymax; ++yp) {
                    P cpt(xp,yp);
                    int SOP1 = sideOf(s1,f1,cpt);
                    if (SOP1 != SO1) continue;
                    int SOP2 = sideOf(s2,f2,cpt);
                    if (SOP2 != SO2) continue;
                    int SOP3 = sideOf(i1,i2,cpt);
                    if (SOP3 != SO3) continue;
                    ++ipts;
                }
            }
            ans += ipts;
        } else {
            vector<P> tripts{s1,s2,i2};
            ll area2 = llabs(polygonArea2(tripts));
            ll bpts = acps(s1,s2) + acps(s2,i2) + acps(s1,i2) - 3;
            ll ipts = (area2 - bpts + 2) / 2;
            ipts += (acps(i2,s2) - 2);

            // now need to compute in small triangle
            Q ds1 = dhull[(i+1)%n];
            Q df1 = dhull[(i+2)%n];
            Q ds2 = dhull[i];
            Q df2 = dhull[(i+n-1)%n];
            pair<int, Q> inter = lineInter(ds1, df1, ds2, df2);
            // if (inter.F != 1) return inf();
            assert(inter.F == 1);
            Q ip = inter.S;
            ll xmin = min(min((ll)ip.x, i1.x), i2.x) - 1000;
            ll xmax = max(max((ll)ip.x, i1.x), i2.x) + 1000;
            ll ymin = min(min((ll)ip.y, i1.y), i2.y) - 1000;
            ll ymax = max(max((ll)ip.y, i1.y), i2.y) + 1000;

            int SO1 = sideOf(s1,f1,i2);
            int SO2 = sideOf(s2,f2,i1);
            int SO3 = sideOf(i1,i2,f2) * (-1);
            assert(SO1 != 0);
            assert(SO2 != 0);
            assert(SO3 != 0);

            for (ll xp = xmin; xp <= xmax; ++xp) {
                for (ll yp = ymin; yp <= ymax; ++yp) {
                    P cpt(xp,yp);
                    int SOP1 = sideOf(s1,f1,cpt);
                    if (SOP1 != SO1) continue;
                    int SOP2 = sideOf(s2,f2,cpt);
                    if (SOP2 != SO2) continue;
                    int SOP3 = sideOf(i1,i2,cpt);
                    if (SOP3 != SO3) continue;
                    ++ipts;
                }
            }
            ans += ipts;
        }
    }

    print(ans);

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