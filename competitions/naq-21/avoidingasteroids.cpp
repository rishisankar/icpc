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
vector<P> circleLine(P c, double r, P a, P b) {
	P ab = b - a, p = a + ab * (c-a).dot(ab) / ab.dist2();
	double s = a.cross(b, c), h2 = r*r - s*s / ab.dist2();
	if (h2 < 0) return {};
	if (h2 == 0) return {p};
	P h = ab.unit() * sqrt(h2);
	return {p - h, p + h};
}

bool checkInCyl(ld r, ld x, ld y, ld z) {
    ld dist = sqrt(x*x+y*y);
    return dist <= r && z >= 0;
}

ld getZ(ld x1,ld y1,ld z1, ld x2,ld y2,ld z2, ld a, ld b) {
    if (y2 == y1) return z1 + (z2-z1) * (a - x1) / (x2 - x1);
    else return z1 + (z2-z1) * (b - y1) / (y2 - y1);
}

bool onSameSide(ld x1,ld y1,ld z1, ld x2,ld y2,ld z2, ld a, ld b) {
    ld vx1 = x2-x1;
    ld vy1 = y2-y1;
    ld vz1 = z2-z1;
    ld c = getZ(x1,y1,z1,x2,y2,z2,a,b);
    ld vx2 = a-x1;
    ld vy2 = b-y1;
    ld vz2 = c-z1;
    ld dot = vx1*vx2+vy1*vy2+vz1*vz2;
    return dot > 0;
}

bool inSegment(ld x1,ld y1,ld z1, ld x2,ld y2,ld z2, ld a, ld b) {
    return onSameSide(x1,y1,z1,x2,y2,z2,a,b) && onSameSide(x2,y2,z2,x1,y1,z1,a,b);
}

bool checkIntersection(ld sx, ld sy, ld sz, ld bx, ld by, ld bz, ld r) {
    dbg("checking intersection", sx,sy,sz,bx,by,bz,r);
    Point<ld> c(0,0);
    Point<ld> a(sx,sy);
    Point<ld> b(bx,by);

    if (checkInCyl(r,sx,sy,sz) || checkInCyl(r,bx,by,bz)) return true;

    if (a.x == b.x && a.y == by) return false;

    vector<Point<ld>> intersect = circleLine(c, r, a, b);

    if (intersect.size() == 0) {
        return false;
    } else if (intersect.size() == 1) {
        ld x = intersect[0].x;
        ld y = intersect[0].y;
        return (inSegment(sx,sy,sz,bx,by,bz,x,y) && getZ(sx,sy,sz,bx,by,bz,x,y) >= 0);
    } else {
        ld x0 = intersect[0].x;
        ld y0 = intersect[0].y;
        ld x1 = intersect[1].x;
        ld y1 = intersect[1].y;
        dbg(x0,y0,x1,y1);
        dbg(getZ(sx,sy,sz,bx,by,bz,x0,y0));
        dbg(getZ(sx,sy,sz,bx,by,bz,x1,y1));
        return ( (inSegment(sx,sy,sz,bx,by,bz,x0,y0) && getZ(sx,sy,sz,bx,by,bz,x0,y0) >= 0) ||
            (inSegment(sx,sy,sz,bx,by,bz,x1,y1) && getZ(sx,sy,sz,bx,by,bz,x1,y1) >= 0)  );
    }
}

// void run() {
//     ld sx, sy, sz, bx, by, bz, r;
//     cin >> sx >> sy >> sz >> bx >> by >> bz >> r;
//     cout << (checkIntersection(sx,sy,sz,bx,by,bz,r) ? "intersect" : "no intersect") << '\n';
// }


array<ld, 3> compute(ld matrix[3][3], array<ld, 3> v) {
	array<ld, 3> out { 0, 0, 0 };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			out[i] += matrix[i][j] * v[j];
		}
	}
	return out;
}

void run() {
	ld sx, sy, sz;
	cin >> sx >> sy >> sz;
	ld bx, by, bz;
	cin >> bx >> by >> bz;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		ld px, py, pz;
		cin >> px >> py >> pz;
		ld dx, dy, dz;
		cin >> dx >> dy >> dz;
		int m;
		cin >> m;
		ld dist = 0;
		for (int j = 0; j < m; j++) {
			double cx, cy, cz;
			cin >> cx >> cy >> cz;
			dist = max(dist,
					(cx - px) * (cx - px) + (cy - py) * (cy - py)
							+ (cz - pz) * (cz - pz));
		}
		dist = sqrt(dist);
		array<ld, 3> eP { dx, dy, dz };
		ld theta = -atan2(dx, dy);
		ld matrix[3][3] { { cos(theta), -sin(theta), 0 }, { sin(theta), cos(
				theta), 0 }, { 0, 0, 1 } };
		array<ld, 3> tV = compute(matrix, eP);
		ld theta1 = -atan2(tV[1], tV[2]);
		ld matrix2[3][3] { { 1, 0, 0 }, { 0, cos(theta1), -sin(theta1) }, { 0,
				sin(theta1), cos(theta1) } };
		ld cM[3][3] { };
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					cM[i][k] += matrix[i][j] * matrix2[j][k];
				}
			}
		}
		array<ld,3> mStart=compute(cM,{sx-px,sy-py,sz-pz});
		array<ld,3> mBase= compute(cM,{bx-px,by-py,bz-pz});

        if (checkIntersection(mStart[0],mStart[1],mStart[2], mBase[0], mBase[1], mBase[2], dist)) {
            print("Surrender");
            return;
        } else {
            dbg("Go");
        }
	}
    print("Go");
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