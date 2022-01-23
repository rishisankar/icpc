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

// projection of point onto line
// is colinear point on line segment/ray
// distance between point and line/ray/segment
// distance between line segment and line/ray/segment
// test if point on lines
// not well tested lol

template<class T> struct Point3D {
	typedef Point3D P;
	typedef const P& R;
	T x, y, z;
	explicit Point3D(T x=0, T y=0, T z=0) : x(x), y(y), z(z) {}
	bool operator<(R p) const {
		return tie(x, y, z) < tie(p.x, p.y, p.z); }
	bool operator==(R p) const {
		return tie(x, y, z) == tie(p.x, p.y, p.z); }
	P operator+(R p) const { return P(x+p.x, y+p.y, z+p.z); }
	P operator-(R p) const { return P(x-p.x, y-p.y, z-p.z); }
	P operator*(T d) const { return P(x*d, y*d, z*d); }
	P operator/(T d) const { return P(x/d, y/d, z/d); }
	T dot(R p) const { return x*p.x + y*p.y + z*p.z; }
	P cross(R p) const {
		return P(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);
	}
	T dist2() const { return x*x + y*y + z*z; }
	ld dist() const { return sqrt((ld)dist2()); }
	//Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
	ld phi() const { return atan2(y, x); } 
	//Zenith angle (latitude) to the z-axis in interval [0, pi]
	ld theta() const { return atan2(sqrt(x*x+y*y),z); }
	P unit() const { return *this/(T)dist(); } //makes dist()=1
	//returns unit vector normal to *this and p
	P normal(P p) const { return cross(p).unit(); }
	//returns point rotated 'angle' radians ccw around axis
	P rotate(ld angle, P axis) const {
		ld s = sin(angle), c = cos(angle); P u = axis.unit();
		return u*dot(u)*(1-c) + (*this)*c - cross(u)*s;
	}
};


/*
Projection of point P onto line containing points a,b
*/
Point3D<ld> projection(Point3D<ld> P, Point3D<ld> a, Point3D<ld> b) {
  // projection of point on line: A + dot(AP,AB) / dot(AB,AB) * AB
	Point3D<ld> v = b-a;
  ld scale = v.dot(P-a) / v.dot(v);
	return Point3D<ld>(a.x+scale*v.x, a.y+scale*v.y, a.z+scale*v.z);
}

/*
Check if a *colinear* point P is on the ray starting at a and going in direction of b
*/
bool pointOnRay(Point3D<ld> P, Point3D<ld> a, Point3D<ld> b) {
	Point3D<ld> v1 = P-a;
	Point3D<ld> v2 = b-a;
	return v1.dot(v2) >= 0;	
}

/*
Check if a *colinear* point P is on the line segment [a,b]
*/
bool pointOnSegment(Point3D<ld> P, Point3D<ld> a, Point3D<ld> b) {
	return pointOnRay(P,a,b) && pointOnRay(P,b,a);
}

/*
Distance between Point P and other linear thing

type = 0: line segment [a,b]
type = 1: ray starting at a in direction of b
type = 2: line connecting a,b
*/
ld distPoint(Point3D<ld> P, Point3D<ld> a, Point3D<ld> b, int type) {
  Point3D<ld> proj = projection(P, a, b);
  if (type == 2) {
    return (P-proj).dist();
  } else if (type == 1) {
		if (pointOnRay(proj, a, b)) {
			return (P-proj).dist();
		} else {
			return (P-a).dist();
		}
	} else {
		if (pointOnSegment(proj, a, b)) {
			return (P-proj).dist();
		} else {
			return min((P-a).dist(), (P-b).dist());
		}
	}
}

ld distLineSegmentHelper(Point3D<ld> a, Point3D<ld> b, Point3D<ld> c, Point3D<ld> d, int type, ld i) {
	ld nx = a.x + i*(b.x-a.x);
	ld ny = a.y + i*(b.y-a.y);
  ld nz = a.z + i*(b.z-a.z);
	Point3D<ld> np(nx,ny,nz);
	return -distPoint(np, c, d, type);
}

/*
Distance between line segment [a,b] and other linear thing

type = 0: line segment [c,d]
type = 1: ray starting at c in direction of d
type = 2: line connecting c,d

// see avoidingasteroids from naq21
// idea: use ternary search between end points of line segment
*/
ld distLineSegment(Point3D<ld> a, Point3D<ld> b, Point3D<ld> c, Point3D<ld> d, int type) {
  ld l = 0; 
  ld r = 1;
	  ld eps = 1e-9; // ternary search error limit
    while (r - l > eps) {
      ld m1 = l + (r - l) / 3;
      ld m2 = r - (r - l) / 3;
      ld f1 = distLineSegmentHelper(a,b,c,d,type,m1);
      ld f2 = distLineSegmentHelper(a,b,c,d,type,m2);
      if (f1 < f2) l = m1;
      else r = m2;
    }
    return -distLineSegmentHelper(a,b,c,d,type,l); // returns min dist
}


void run() {
    double x1,y11,z1,x2,y2,z2;
	cin >> x1 >> y11 >> z1;
	cin >> x2 >> y2 >> z2;
    Point3D<ld> a(x1,y11,z1);
    Point3D<ld> b(x2,y2,z2);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		double px, py, pz;
		cin >> px >> py >> pz;
		double dx, dy, dz;
		cin >> dx >> dy >> dz;
		int m;
		cin >> m;
		double dist = 0;
		for (int j = 0; j < m; j++) {
			double cx, cy, cz;
			cin >> cx >> cy >> cz;
			dist = max(dist,
					(cx - px) * (cx - px) + (cy - py) * (cy - py)
							+ (cz - pz) * (cz - pz));
		}
        Point3D<ld> c(px,py,pz);
        Point3D<ld> v(dx,dy,dz);
		ld r = sqrt(dist);
        ld opt = distLineSegment(a,b,c,c+v,1);
        if (opt < r) {
            print("Surrender");
            return;
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