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

struct circ {
    Point<ld> center;
    ld r,s;
};

ld timereq(circ& c1, circ& c2) {
    ld dist = (c2.center - c1.center).dist() - c1.r - c2.r;
    return dist / (c1.s + c2.s);
}

vector<circ> ooblect(vector<circ>& circles) {
    // assume last circle is new one
    vector<circ> newcircles;
    int n = circles.size() - 1;
    Point<ld> sum_cent = circles[n].center;
    ld sum_r2 = circles[n].r*circles[n].r;
    ld merge_s = circles[n].s;
    int merge_n = 1;
    REP(i, n) {
        if ((circles[n].center - circles[i].center).dist() <= circles[n].r + circles[i].r) {
            // circles intersect
            sum_cent = sum_cent + circles[i].center;
            sum_r2 += (circles[i].r * circles[i].r);
            merge_s = max(merge_s, circles[i].s);
            ++merge_n;
        } else {
            newcircles.PB(circles[i]);
        }
    }
    circ newc;
    newc.center = Point<ld>(sum_cent.x/merge_n, sum_cent.y/merge_n);
    newc.r = sqrt(sum_r2);
    newc.s = merge_s;
    newcircles.PB(newc);

    return newcircles;
}

vector<circ> reduce(vector<circ> circles) {
    int n = circles.size();
    ld mintime = timereq(circles[0], circles[1]);
    pii best = {0,1};
    REP(i, n) {
        for (int j = i+1; j < n; ++j) {
            ld tr = timereq(circles[i], circles[j]);
            if (tr < mintime){
                mintime = tr;
                best = {i,j};
            }
        }
    }
    // best represents circles that will intersect first.
    // next, simulate that amount of time passing...
    REP(i, n) {
        circles[i].r += circles[i].s * mintime;
    }
    // combine {i,j} from best (note j > i guaranteed)
    int i = best.F;
    int j = best.S;
    circ newcirc;
    newcirc.center = Point<ld>((circles[i].center.x+circles[j].center.x)/2, (circles[i].center.y+circles[j].center.y)/2);
    newcirc.r = sqrt(circles[i].r*circles[i].r + circles[j].r*circles[j].r);
    newcirc.s = max(circles[i].s, circles[j].s);
    circles.PB(newcirc);
    circles.erase(circles.begin() + j);
    circles.erase(circles.begin() + i);

    int circlen = circles.size();
    while (true) {
        circles = ooblect(circles);
        if (circlen == circles.size()) break;
        circlen = circles.size();
    }

    return circles;
}

void run() {
    int n; cin >> n;
    vector<circ> circles;
    REP(i, n) {
        ld x,y,r,s; cin >> x >> y >> r >> s;
        circ c;
        c.center = Point<ld>(x,y);
        c.r = r; c.s=s;
        circles.PB(c);
    }

    while (n > 1) {
        circles = reduce(circles);
        n = circles.size();
    }

    print(circles[0].center.x, circles[0].center.y);
    print(circles[0].r);

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