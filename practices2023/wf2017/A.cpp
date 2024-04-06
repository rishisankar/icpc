
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
            if (A.x > B.x) swap(A,B); // edge case vertical!
            if (A.x == B.x && A.y > B.y) swap(A,B);
            T L = A - (B-A) * 100000000LL;
            T R = B + (B-A) * 100000000LL;

            vector<pair<Q, int>> events; //events: 0 = toggle, 1 = inside, 2 = outside

            rep(i,0,n) {
                T X = pts[i];
                T Y = pts[(i+1)%n];
                if ((Y-X).cross(B-A) == 0) {
                    // parallel
                    continue;
                }
                if (sideOf(A,B,X) == 0 || sideOf(A,B,Y) == 0) {
                    // intersection is on endpt, not on interior
                    continue;
                }
                auto p = segInter(gq(L), gq(R), gq(X), gq(Y));
                if (sz(p) > 0) {
                    // intersection on interior
                    events.pb({p[0], 0});
                }
            }

            rep(i,0,n) {
                T X = pts[i];

                if (sideOf(A,B,X) != 0) {
                    // not on line, ignore
                    continue;
                }

                T C = pts[(i+1)%n];
                T D = pts[(i+n-1)%n];
                bool parallelCase = false;
                T Y,Z;
                if (sideOf(A,B,C) == 0) {
                    parallelCase = true;
                    Y = C;
                    Z = D;
                } else if (sideOf(A,B,D) == 0) {
                    parallelCase = true;
                    Y = D;
                    Z = C;
                }

                if (parallelCase) {
                    
                    if (Y.x < X.x || (Y.x == X.x && Y.y < X.y)) {
                        // Y < X : right vertex logic
                        int evt;
                        if (Y == D) {
                            if (sideOf(X,Z,Y) == -1) {
                                evt = 1;
                            } else {
                                evt = 2;
                            }
                        } else {
                            if (sideOf(X,Z,Y) == -1) {
                                evt = 2;
                            } else {
                                evt = 1;
                            }
                        }
                        events.pb({gq(X), evt});
                    } else {
                        // Y > X : left vertex logic
                        events.pb({gq(X), 1});
                    }
                    

                } else {
                    // same / opp side
                    if (sideOf(A,B,C) != sideOf(A,B,D)) {
                        events.pb({gq(X), 0});
                    }
                }

            }

            sort(all(events), [](pair<Q, int>& p1, pair<Q, int>& p2) {
                Q P1 = p1.F, P2 = p2.F;
                return (P1.x < P2.x || (P1.x == P2.x && P1.y < P2.y));
            });

            bool inside = false;
            Q prev = gq(L);
            for (auto ev : events) {
                if (inside) {
                    bst = max(bst, (ev.F-prev).dist());
                }
                bool pi = inside;
                if (ev.S == 0) inside = !pi;
                else if (ev.S == 1) inside = true;
                else if (ev.S == 2) inside = false;
                if (!pi && inside) {
                    prev = ev.F;
                }
            }
        }
    }
    cout << setprecision(20) << bst << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	solve();
}
