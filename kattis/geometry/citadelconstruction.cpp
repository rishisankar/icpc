#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef vector<int> vi;

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

template<class T>
T polygonArea2(vector<Point<T>>& v) {
  T a = v.back().cross(v[0]);
  rep(i,0,sz(v)-1) a += v[i].cross(v[i+1]);
  return abs(a);
}

template<class T>
T triangleArea(Point<T>& p1, Point<T>& p2, Point<T>& p3) {
  T a = p3.cross(p1);
  a += p1.cross(p2);
  a += p2.cross(p3);
  return abs(a);
}

template<class F>
int ternSearch(int a, int b, F f) {
	while (b - a >= 5) {
		int mid = (a + b) / 2;
		if (f(mid) < f(mid+1)) a = mid;
		else b = mid+1;
	}
	rep(i,a+1,b+1) if (f(a) < f(i)) a = i;
	return a;
}

void run() {
  int n; cin >> n;
  vector<P> origPts;
  for (int i = 0; i < n; ++i) {
    ld a,b; cin >> a >> b;
    P pt(a,b);
    origPts.push_back(pt);
  }
  vector<P> pts = convexHull(origPts);
  if (pts.size() <= 2) {
    cout << "0\n";
    return;
  }

  n = pts.size();
  ld best = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i+1; j < n; ++j) {
      vector<Point<ld>> sqr;
      sqr.push_back(pts[i]);
      if (i + 1 != j) {
        int tsv = ternSearch(i+1, j-1, [&](int idx) {
          return triangleArea(pts[i],pts[j],pts[idx]);
        });
        sqr.push_back(pts[tsv%n]);
      }
      sqr.push_back(pts[j]);
      if (i + n != j+1) {
        int tsv = ternSearch(j+1, i+n-1, [&](int idx) {
          return triangleArea(pts[i],pts[j],pts[idx%n]);
        });
        sqr.push_back(pts[tsv%n]);
      }
      
      ld area = polygonArea2(sqr) / 2;

      best = max(best, area);

    }
  }

  ll result = round(best * 10);
  if (result % 10 == 0) {
    cout << result/10 << '\n';
  } else {
    cout << result/10 << '.' << result%10 << '\n';
  }

}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) {
    run();
  }
}