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

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (d == 0) // if parallel
		return {-(s1.cross(e1, s2) == 0), P(0, 0)};
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
}

template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P> vector<P> segInter(P a, P b, P c, P d) {
	auto oa = c.cross(d, a), ob = c.cross(d, b),
	     oc = a.cross(b, c), od = a.cross(b, d);
	// Checks if intersection is single non-endpoint point.
	if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
		return {(a * ob - b * oa) / (ob - oa)};
	set<P> s;
	if (onSegment(c, d, a)) s.insert(a);
	if (onSegment(c, d, b)) s.insert(b);
	if (onSegment(a, b, c)) s.insert(c);
	if (onSegment(a, b, d)) s.insert(d);
	return {all(s)};
}



struct wall {
    ll x1, y1, x2, y2;

    bool isVert() {
        return x1 == x2;
    }

    /* find intersection pt on wall, or return {0,0} if no such pt */
    pair<ld,ld> point_intersect(ld x, ld y, ld vx, ld vy) {
        Point<ld> s1(x,y);
        Point<ld> e1(x+vx,y+vy);
        Point<ld> s2(x1,y1);
        Point<ld> e2(x2,y2);
        pair<int,Point<ld>> inter = lineInter(s1,e1,s2,e2);
        // check intersection pt exists
        if (inter.first != 1) return {0,0};
        Point<ld> res = inter.second;
        // check on line segment
        if (isVert() && (res.y > max(y1,y2) || res.y < min(y1,y2))) return {0,0};
        if ((!isVert()) && (res.x > max(x1,x2) || res.x < min(x1,x2))) return {0,0};
        // check in correct direction
        if (sgn(res.x - x) != sgn(vx) || sgn(res.y - y) != sgn(vy)) return {0,0};
        return {res.x,res.y};
    }
};

int n;
ll x,y;
vector<wall> walls;

/* return scaled end coord, or LLONG_MAX if fail */
ll scalar(ll end, vector<ll> scale) {
    if (scale.size() == 0) return end;
    scale.PB(end);
    // assuming walls cannot be on an axis...    
    bool posDir = (scale[0] > 0);
    ll curPos = 0;
    ll totalDist = 0;
    for (int i = 0; i < scale.size(); ++i) {
        if ((curPos < scale[i] && posDir) || (curPos > scale[i] && (!posDir))) {
            totalDist += abs(curPos - scale[i]);
            curPos = scale[i];
            posDir = !posDir;
        } else {
            return LLONG_MAX;
        }
    }
    if (scale[0] > 0) return totalDist;
    else return -totalDist;
}

// returns the number of walls hit, or -1 if the ordering is invalid
int test(vector<int> perm) {
    vector<ll> xscale, yscale;
    int ct = 0;
    for (int i : perm) {
        if (i == n) break;
        ++ct;
        if (walls[i].isVert()) {
            xscale.PB(walls[i].x1);
        } else {
            yscale.PB(walls[i].y1);
        }
    }

    ll nx = scalar(x, xscale);
    ll ny = scalar(y, yscale);
    if (nx == LLONG_MAX || ny == LLONG_MAX) return -1;

    /*
    1) find intersection point on next wall (fail if no pt)
    2) for all not-hit walls, check line segment intersection with motion (fail if intersect)
    3) reflect trajectory vector and update cur pt
    */

    unordered_set<int> wallsHit;
    ld cx = 0;
    ld cy = 0;
    ld vx = nx;
    ld vy = ny;

    for (int i : perm) {
        if (i == n) break;
        pair<ld,ld> newpt = walls[i].point_intersect(cx, cy, vx, vy);
        if (newpt.first == 0 && newpt.second == 0) return -1;
        Point<ld> s1(cx,cy);
        Point<ld> e1(newpt.first, newpt.second);
        REP(j,n) {
            if (j == i || wallsHit.count(j)) continue;
            Point<ld> s2(walls[j].x1,walls[j].y1);
            Point<ld> e2(walls[j].x2,walls[j].y2);
            vector<Point<ld>> seg = segInter(s1,e1,s2,e2);
            if (seg.size() > 0) return -1;
        }
        wallsHit.insert(i);
        if (walls[i].isVert()) {
            vx *= -1;
        } else {
            vy *= -1;
        }
        cx = newpt.first;
        cy = newpt.second;
    }

    // test trajectory is correct here?
    Point<ld> s1(cx,cy);
    Point<ld> e1(x,y);
    REP(j, n) {
        if (wallsHit.count(j)) continue;
        Point<ld> s2(walls[j].x1,walls[j].y1);
        Point<ld> e2(walls[j].x2,walls[j].y2);
        vector<Point<ld>> seg = segInter(s1,e1,s2,e2);
        if (seg.size() > 0) return -1;
    }

    return ct;
}

void run() {
    cin >> n;
    cin >> x >> y;
    walls.resize(n);
    REP(i, n) {
        cin >> walls[i].x1 >> walls[i].y1 >> walls[i].x2 >> walls[i].y2;
    }

    int best = -1;

    vector<int> perm;
    REP(i, n+1) {
        perm.PB(i);
    }

    do {
        best = max(best, test(perm));
    } while (next_permutation(all(perm)));

    if (best == -1) {
        print("impossible");
    } else {
        print(best);
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