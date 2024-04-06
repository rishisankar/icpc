
#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a,x) for (auto& a: x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define F first
#define S second
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) {
	return os << '(' << p.first << ", " << p.second << ')';
}
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) {
	os << '{';
	string sep;
	for (const auto &x: v) os << sep << x, sep = ", ";
	return os << '}';
}

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) {
	cerr << ' ' << H; dbg_out(T...);
}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
const int MOD = 1e9+7;

typedef long double ld;

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

template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (d == 0) // if parallel
		return {-(s1.cross(e1, s2) == 0), P(0, 0)};
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
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

template<class P>
bool inPolygon(vector<P> &p, P a, bool strict = true) {
	int cnt = 0, n = sz(p);
	rep(i,0,n) {
		P q = p[(i + 1) % n];
		if (onSegment(p[i], q, a)) return !strict;
		//or: if (segDist(p[i], q, a) <= eps) return !strict;
		cnt ^= ((a.y<p[i].y) - (a.y<q.y)) * a.cross(p[i], q) > 0;
	}
	return cnt;
}

template<class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

typedef Point<ll> T;
typedef Point<ld> Q;

Q gq(T t) {
    return Q(t.x,t.y);
}

void solve() {
    int n; cin >> n;
    vector<T> pts;
    rep(i,0,n) {
        ll a,b; cin >> a >> b;
        pts.emplace_back(a,b);
    }
    ld bst = 0;
    rep(ii,0,n) {
        rep(jj,ii+1,n) {
            T A = pts[ii];
            T B = pts[jj];
            Q gA = gq(A), gB = gq(B);
            if (jj == ii+1 || (ii == 0 && jj == n-1)) {
                bst = max(bst, (B-A).dist());
                continue;
            }

            int ss1 = sideOf(A,B,pts[(ii+1)%n]);
            int ss2 = sideOf(A,B,pts[(ii+n-1)%n]);
            if (ss1 == 0 || ss2 == 0 || ss1 == ss2) continue;
            ss1 = sideOf(A,B,pts[(jj+1)%n]);
            ss2 = sideOf(A,B,pts[(jj+n-1)%n]);
            if (ss1 == 0 || ss2 == 0 || ss1 == ss2) continue;

            if (A.x > B.x) swap(A,B); // edge case vertical!
            if (A.x == B.x && A.y > B.y) swap(A,B);
            T pmin = A - (B-A) * 100000000LL;
            T pmax = B + (B-A) * 100000000LL;
            Q L = gq(pmin), R = gq(pmax);

            bool valid = true;
            vector<Q> bad;

            rep(i,0,n) {
                T X = pts[i];
                T Y = pts[(i+1)%n];
                T Z = pts[(i+n-1)%n];

                if ((Y-X).cross(B-A) == 0) {
                    // parallel
                    continue;
                }
                if (sideOf(A,B,X) == 0) {
                    // X on line
                    if (sideOf(A,B,Y) != sideOf(A,B,Z)) {
                        // X is a bad point
                        if (!(X == A) && !(X == B) && onSegment(A,B,X)) {
                            valid = false;
                            break;
                        }
                        bad.pb(gq(X));
                    }
                }
                if (sideOf(A,B,Y) != 0) {
                    auto p = segInter(gq(pmin), gq(pmax), gq(X), gq(Y));
                    if (sz(p) > 0) {
                        assert(sz(p) == 1);
                        // p[0] is a bad point
                        bad.pb(p[0]);
                    }
                }
            }
            for (Q q : bad) {
                if (!(q == gA) && !(q == gB) && onSegment(gA, gB, q)) {
                    valid = false;
                }
            }

            if (!valid) continue;
            for (Q q : bad) {
                if (A.x == B.x) {
                    if (q.y < ((gA+gB)/2.).y) {
                        L.y = max(L.y, q.y);
                    } else {
                        R.y = min(R.y, q.y);
                    }
                } else {
                    if (q.x > ((gA+gB)/2.).x) {
                        if (R.x > q.x) {
                            R = q;
                        }
                    } else {
                        if (L.x < q.x) {
                            L = q;
                        }
                    }
                }
            }
            // if ((R-L).dist() > 100) {
            //     dbg((R-L).dist());
            //     dbg(A.x,A.y);
            //     dbg(B.x,B.y);
            //     dbg(R.x,R.y);
            //     dbg(L.x,L.y);
            //     dbg(sz(bad));
            //     for (auto p : bad) dbg(p.x,p.y);
            //     exit(0);
            // }
            bst = max(bst, (R-L).dist());
        }
    }
    cout << setprecision(20) << bst << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	solve();
}
