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

typedef Point<ld> P;
bool circleInter(P a,P b,double r1,double r2,pair<P, P>* out) {
	if (a == b) { assert(r1 != r2); return false; }
	P vec = b - a;
	double d2 = vec.dist2(), sum = r1+r2, dif = r1-r2,
	       p = (d2 + r1*r1 - r2*r2)/(d2*2), h2 = r1*r1 - p*p*d2;
	if (sum*sum < d2 || dif*dif > d2) return false;
	P mid = a + vec*p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
	*out = {mid + per, mid - per};
	return true;
}

vector<P> circleLine(P c, double r, P a, P b) {
	P ab = b - a, p = a + ab * (c-a).dot(ab) / ab.dist2();
	double s = a.cross(b, c), h2 = r*r - s*s / ab.dist2();
	if (h2 < 0) return {};
	if (h2 == 0) return {p};
	P h = ab.unit() * sqrt(h2);
	return {p - h, p + h};
}

const ld eps = 1e-11;

ld w,h;

// ang from [-pi,pi] --> (0,2pi]
ld normAngle(ld ang) {
    if (ang <= 0) return ang+2*pi;
    else return ang;
}

// expand radius by r, get rid of any circles inside another circle
vector<pair<P,ld>> parseCircles(vector<pair<P,ld>> circles, ld r) {
    int n = circles.size();
    REP(i,n) circles[i].S += r; // expand radius by r
    vector<bool> validCircle(n, true);
    REP(i, n) {
        REP(j, n) {
            if (i==j) continue;
            // circle is inside another if: (no intersection or 1 intersection) && (two boundary pts inside other circle)
            pair<P,P> outI;
            bool b = circleInter(circles[i].F, circles[j].F, circles[i].S, circles[j].S, &outI);
            if (b && !(outI.F == outI.S)) continue;
            P pt1(circles[i].F.x + circles[i].S, circles[i].F.y);
            P pt2(circles[i].F.x - circles[i].S, circles[i].F.y);
            pt1 = pt1 - circles[j].F;
            pt2 = pt2 - circles[j].F;
            if (pt1.dist2() <= circles[j].S*circles[j].S && pt2.dist2() <= circles[j].S*circles[j].S) {
                // circle i inside circle j
                validCircle[i] = false;
                break;
            }
        }
    }
    vector<pair<P,ld>> outputCircles;
    REP(i,n) {
        if (validCircle[i]) {
            outputCircles.PB(circles[i]);
        }
    }
    return outputCircles;
}

bool check(ld r, vector<pair<P,ld>>& inpCircles) {
    /* 
    goal: check if can draw circle of radius r somewhere in square
    1) expand each circ's radius by r : there is a pt not on any circle <-> can draw circle of radius r
    2) for each circle:
        - cut any part inside another circle
        - cut any part outside box (shrink box by r also)
    */
    vector<pair<P,ld>> circles = parseCircles(inpCircles, r);
    int n = circles.size();
    REP(i, n) {
        vector<pair<ld,ld>> intervals;

        // left vertical line
        if (circles[i].F.x + circles[i].S < r) continue;
        vector<P> ln = circleLine(circles[i].F, circles[i].S, P(r,0), P(r,h));
        if (ln.size() == 2) {
            ld ang1 = normAngle((ln[0]-circles[i].F).angle());
            ld ang2 = normAngle((ln[1]-circles[i].F).angle());
            if (ang1 > ang2) swap(ang1,ang2);
            intervals.PB({ang1, ang2});
        }

        // right vertical line
        if (circles[i].F.x - circles[i].S > w-r) continue;
        ln = circleLine(circles[i].F, circles[i].S, P(w-r,0), P(w-r,h));
        if (ln.size() == 2) {
            ld ang1 = normAngle((ln[0]-circles[i].F).angle());
            ld ang2 = normAngle((ln[1]-circles[i].F).angle());
            if (ang1 > ang2) swap(ang1,ang2);
            // dbg("rv",ang1,ang2);
            intervals.PB({0,ang1});
            intervals.PB({ang2,2*pi});
        }

        // bottom horizontal line
        if (circles[i].F.y + circles[i].S < r) continue;
        ln = circleLine(circles[i].F, circles[i].S, P(0,r), P(w,r));
        if (ln.size() == 2) {
            ld ang1 = normAngle((ln[0]-circles[i].F).angle());
            ld ang2 = normAngle((ln[1]-circles[i].F).angle());
            if (ang1 > ang2) swap(ang1,ang2);
            if (ang1 < pi) {
                // dbg("bh",ang1,ang2);
                intervals.PB({0,ang1});
                intervals.PB({ang2,2*pi});
            } else {
                // dbg("bh2",ang1,ang2);
                intervals.PB({ang1, ang2});
            }
        }

        // top horizontal line
        if (circles[i].F.y - circles[i].S > h-r) continue;
        ln = circleLine(circles[i].F, circles[i].S, P(0,h-r), P(w,h-r));
        if (ln.size() == 2) {
            ld ang1 = normAngle((ln[0]-circles[i].F).angle());
            ld ang2 = normAngle((ln[1]-circles[i].F).angle());
            if (ang1 > ang2) swap(ang1,ang2);
            if (ang1 < pi) {
                // dbg("th1",ang1,ang2);
                intervals.PB({ang1, ang2});
            } else {
                // dbg("th2",ang1,ang2);
                intervals.PB({0,ang1});
                intervals.PB({ang2,2*pi});
            }
        }

        REP(j, n) {
            if (i == j) continue;
            pair<P,P> outI;
            bool b = circleInter(circles[i].F, circles[j].F, circles[i].S, circles[j].S, &outI);
            if (!b || outI.F == outI.S) continue;
            ld ang1 = normAngle((outI.F-circles[i].F).angle());
            ld ang2 = normAngle((outI.S-circles[i].F).angle());
            if (ang1 > ang2) swap(ang1,ang2);
            ld avgAng = (ang1+ang2)/2;
            P midP(circles[i].S,0);
            midP = midP.rotate(avgAng);
            midP = midP + circles[i].F;
            if ((midP-circles[j].F).dist2() <= circles[j].S*circles[j].S) {
                intervals.PB({ang1,ang2});
            } else {
                intervals.PB({0,ang1});
                intervals.PB({ang2,2*pi});
            }
        }
        // print("Circle", i, circles[i].F.x, circles[i].F.y, circles[i].S);
        // for (pair<ld,ld> pp : intervals) {
        //     print(pp.F, pp.S);
        // }

        // circular sweep line to find a point if possible
        sort(all(intervals));
        if (intervals.size() == 0) return true;
        if (intervals[0].F > 0) return true;
        ld curEnd = intervals[0].S;
        for (int iv = 1; iv < intervals.size(); ++iv) {
            if (intervals[iv].F > curEnd) return true;
            curEnd = max(curEnd, intervals[iv].S);
        }
        if (curEnd < 2*pi) return true;
    }
    return false;
}

void run() {
    // pair<P,P> outI;
    // P c1(0,0);
    // P c2(1,0);

    // bool b = circleInter(c1,c2,1,1,&outI);
    // print(b,outI.F.x,outI.F.y, outI.S.x, outI.S.y);

    // b = circleInter(c2,c1,1,1,&outI);
    // print(b,outI.F.x,outI.F.y, outI.S.x, outI.S.y);

    int n;
    cin >> w >> h;
    cin >> n;

    // get rid of duplicate circles, if any
    set<tuple<ld,ld,ld>> circlesOrig;
    REP(i, n) {
        ld a,b,c; cin >> a >> b >> c;
        circlesOrig.insert({a,b,c});
    }
    n = circlesOrig.size();
    vector<pair<P, ld>> circles;
    for (tuple<ld,ld,ld> tup : circlesOrig) {
        P p(get<0>(tup), get<1>(tup));
        circles.PB({p, get<2>(tup)});
    }

    ld lo = 0;
    ld hi = min(w,h) / 2;
    while (abs(hi-lo) > eps && abs((hi-lo)/lo) > eps) {
        ld mid = (hi+lo)/2;
        if (check(mid, circles)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    print(lo);
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