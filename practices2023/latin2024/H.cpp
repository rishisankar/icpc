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

template<typename T> inline T ceildiv(T a, T b) {return (a+b-1)/b;}

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

ld ep = 1e-10;
ld beps = 1e-8;

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
vector<P> circleLine(P c, ld r, P a, P b) {
	P ab = b - a, p = a + ab * (c-a).dot(ab) / ab.dist2();
	ld s = a.cross(b, c), h2 = r*r - s*s / ab.dist2();
	if (h2 < 0) return {};
	if (h2 == 0) return {p};
	P h = ab.unit() * sqrtl(h2);
	return {p - h, p + h};
}

typedef Point<ld> T;

int n;
ld d;

vector<pair<T,T>> lines;

bool addSweep(vector<pair<ld, int>> &sweep, ld a1, ld a2) {
    // dbg("sweep", a1, a2);
    a1 += ep;
    a2 -= ep;
    a1 = max(a1,0.L);
    a2 = min(a2,2*pi);
    if (a1 < a2) {
        // dbg("adding inv", a1, a2);
        sweep.pb({a1,1});
        sweep.pb({a2,0});
        return true;
    }
    return false;
}

// return true if bear still healthy using the first k<=n lines
bool test(int k) {
    T c(0,0);
    bool zcov = false;
    vector<pair<ld, int>> sweep;
    rep(i,0,k) {
        vector<T> inter = circleLine(c,d,lines[i].F,lines[i].S);
        if (sz(inter) < 2) continue; // doesn't impact bear
        ld a1 = atan2l(inter[0].y, inter[0].x);
        ld a2 = atan2l(inter[1].y, inter[1].x);
        if (a1 < 0) a1 += 2*pi;
        if (a2 < 0) a2 += 2*pi;
        if (a2 < a1) swap(a1,a2);
        if (a2-a1 < pi) {
            addSweep(sweep,a1,a2);
        } else {
            bool b1 = addSweep(sweep,0,a1);
            bool b2 = addSweep(sweep,a2,2*pi);
            if (b1||b2) {
                zcov = true;
            }
        }
    }
    if (!zcov) return true;

    sort(all(sweep));
    ld start, end;
    int invc=0, ctr = 0;
    for (auto p : sweep) {
        if (p.S == 1) {
            if (ctr == 0) {
                if (invc != 0) return true;
                invc++;
                start = p.F; 
            }
            ++ctr;
        } else {
            --ctr;
            if (ctr == 0) end = p.F;
            if (ctr < 0) return false; // shouldn't be possible
        }
    }
    // dbg(start,end, start<beps, 2*pi-end<beps);
    if (start < beps && 2*pi-end < beps) return false;
    return true;
}

void run() {
    cin >> n >> d;
    
    rep(i,0,n) {
        T pt1, pt2;
        cin >> pt1.x >> pt1.y >> pt2.x >> pt2.y;
        lines.pb({pt1,pt2});
    }

    // rep(i,0,n+1) {
    //     bool b = test(i);
    //     dbg(i,b);
    // }

    int bst = n+1;
    int lo = 0, hi = n;
    while (lo <= hi) {
        int mid = (lo+hi)/2;
        if (test(mid)) {
            lo = mid+1;
        } else {
            bst = mid;
            hi = mid-1;
        }
    }
    if (bst == n+1) {
        print("*");
    } else print(bst);
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