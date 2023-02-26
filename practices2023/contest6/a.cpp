#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i  < (b); i++)
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define trav(a, x) for(auto& a: x)
#define F first
#define S second
#define pb push_back
#define mp make_pair


typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v)
{
  os << '{'; string sep; for(const auto &x: v) os << sep << x, sep = ", "; return os << '}'; 
}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ")";
}

void dbg_out() { cerr << endl; }

template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...);}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif


typedef pair<ll,ll> pll;

void rf(pll& p) {
  if (p.F == 0) p = {0,1};
  else {
    ll g = __gcd(abs(p.F), abs(p.S));
    p = {p.F/g, p.S/g};
    if (p.S < 0) p = {-p.F, -p.S};
  }
}

pll af(pll p1, pll p2) {
  pll res = {p2.S*p1.F+p2.F*p1.S, p1.S*p2.S};
  rf(res);
  return res;
}

pll sf(pll p1, pll p2) {
  pll res = {p2.S*p1.F-p2.F*p1.S, p1.S*p2.S};
  rf(res);
  return res;
}

pll mf(pll p1, pll p2) {
  pll res = {p1.F*p2.F, p1.S*p2.S};
  rf(res); return res;
}

pll df(pll p1, pll p2) {
  pll swp = {p2.S,p2.F};
  return mf(p1,swp);
}

bool lt(pll p1, pll p2) {
  rf(p1); rf(p2);
  return p1.F*p2.S < p1.S*p2.F;
}

bool gt(pll p1, pll p2) {
  rf(p1); rf(p2);
  return p1.F*p2.S > p1.S*p2.F;
}

typedef pll T;

int sgn(T x) { rf(x); return (x.F > 0) - (x.F < 0); }

struct Point {
  typedef Point P;
  T x,y;
  explicit Point(T x={0,1}, T y={0,1}) : x(x), y(y) {rf(x),rf(y);}
  P operator+(P p) const { return P(af(x,p.x), af(y,p.y)); }
  P operator-(P p) const { return P(sf(x,p.x), sf(y,p.y)); }
  P operator*(T d) const { return P(mf(x,d), mf(y,d)); }
  P operator/(T d) const { return P(df(x,d), df(y,d)); }
  T cross(P p) const { return sf(mf(x, p.y), mf(y,p.x)); }
  T cross(P a, P b) const { return (a-*this).cross(b-*this);}
  T dot(P p) const { return af(mf(x,p.x),mf(y,p.y)); }
  pll dist2() const { return af(mf(x,x), mf(y,y)); }
  bool operator==(P p) const { return x == p.x && y == p.y; }
};
typedef Point P;

pll polygonArea2(vector<P>& v) {
  T a = v.back().cross(v[0]);
  rep(i,0,sz(v)-1) a = af(a,v[i].cross(v[i+1]));
  return a;
}

bool onSegment(P s, P e, P p) {
  pll zero = {0,1};
	return p.cross(s, e) == zero && (s - p).dot(e - p).F <= 0;
}

bool inPolygon(vector<P> &p, P a, bool strict = true) {
	int cnt = 0, n = sz(p);
	rep(i,0,n) {
		P q = p[(i + 1) % n];
		if (onSegment(p[i], q, a)) return !strict;
		//or: if (segDist(p[i], q, a) <= eps) return !strict;
    pll scl = {(lt(a.y,p[i].y) - lt(a.y,q.y)), 1};
    rf(scl);
		cnt ^= gt(mf(scl, a.cross(p[i], q)),{0LL,1LL});
	}
	return cnt;
}

vector<P> segInter(P a, P b, P c, P d) {
  pll oa = c.cross(d,a), ob = c.cross(d,b), oc = a.cross(b,c), od = a.cross(b,d);
  // 1 intersection point
  if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0) return { (a*ob - b*oa) / sf(ob,oa)};
	vector<P> s;
	if (onSegment(c, d, a)) s.pb(a);
	if (onSegment(c, d, b)) s.pb(b);
	if (onSegment(a, b, c) && (!(c==a)) && (!(c==b))) s.pb(c);
	if (onSegment(a, b, d) && (!(d==a)) && (!(d==b))) s.pb(d);
	return s;
}

int N;

int getedge(vector<P>& pixel, P pt) {
  rep(i,0,4) {
    if (pixel[i] == pt) return i;
  }
  rep(i,0,4) {
    P a = pixel[i];
    P b = pixel[(i+1)%4];
    if (onSegment(a,b,pt)) return i;
  }
  return -1;
}

vector<P> removedups(vector<P>& pol) {
  int z = pol.size();
  vector<P> npol;
  if (pol.size() == 0) return npol;
  npol.pb(pol[0]);
  for (int i = 1; i < z; ++i) {
    if (!(npol.back() == pol[i])) npol.pb(pol[i]);
  }
  if (npol.size() >= 2 && npol.front() == npol.back()) npol.pop_back();
  return npol;
}

void test(vector<P>& points, ll r, ll c) {
  vector<P> pixel;
  pixel.pb(P({r,1},{c,1}));  // corner 0
  pixel.pb(P({r,1},{c+1,1}));  // corner 1
  pixel.pb(P({r+1,1},{c+1,1}));  // corner 2
  pixel.pb(P({r+1,1},{c,1}));  // corner 3

  // check cases: fully inside, fully not inside
  // fully inside... all inside polygon
  bool succeed = true;
  rep(i,0,4) {
    if (!inPolygon(points, pixel[i], false)) { succeed = false; break; }
  }
  if (succeed) {
    cout << "1/1\n";
    return;
  }
  // fully not inside... all outside polygon
  succeed = true;
  rep(i,0,4) {
    if (inPolygon(points, pixel[i], true)) { succeed = false; break; }
  }
  // also need to check that all intersections only have corner if at all
  unordered_set<int> corners;
  rep(i,0,N) {
    P a = points[i];
    P b = points[(i+1)%N];
    rep(j,0,4) {
      P c = pixel[j];
      P d = pixel[(j+1)%4];
      vector<P> sinter = segInter(a,b,c,d);
      for (P pint : sinter) {
        if (pint == c) corners.insert(j);
        else if (pint == d) corners.insert((j+1)%4);
        else {
          succeed = false;
          break;
        }
      }
    }
  }
  dbg(corners.size());
  // for (int x : corners) dbg(i,x);
  if (corners.size() > 1) succeed = false;
  if (succeed) {
    cout << "0/1\n";
    return;
  }

  pll centerx = mp(2*r+1,2LL);
  pll centery = mp(2*c+1,2LL);
  
  vector<P> pol;
  rep(i, 0, N) {
    P a = points[i];
    P b = points[(i+1)%N];
    if (a.x == centerx && a.y == centery) {
      pol.push_back(a);
    }
    vector<P> its;
    rep(j,0,4) {
      P c = pixel[j];
      P d = pixel[(j+1)%4];
      vector<P> itsX = segInter(a,b,c,d);
      for (Point p : itsX) its.pb(p);
    }
    // sort its by distance to a!
    sort(all(its), [&](const P p1, const P p2) {
      return lt((p1-a).dist2(),(p2-a).dist2());
    });
    // need to add corners if prev and new pt are not on the same line seg (special case for center? idts)
    if (its.size() > 0) {
      if (pol.size() > 0) {
        P last = pol.back();
        if (!(last.x == centerx && last.y == centery)) {
          // point on corner
          int eg1 = getedge(pixel, last);
          int eg2 = getedge(pixel, its[0]);
          if (eg1 != -1 && eg2 != -1) {
            if (eg1 <= eg2) {
              for (int cr = eg1+1; cr <= eg2; ++cr) {
                pol.push_back(pixel[cr]);
              }
            } else {
              for (int cr = eg1+1; cr < 4; ++cr) {
                pol.push_back(pixel[cr]);
              }
              for (int cr = 0; cr <= eg2; ++cr) {
                pol.push_back(pixel[cr]);
              }
            }
          }
        }
      }
    }
    for (P p : its) pol.push_back(p);
  }
  if (pol.size() >= 2) {
    int eg1 = getedge(pixel, pol.back());
    int eg2 = getedge(pixel, pol.front());
    if (eg1 != -1 && eg2 != -1) {
      if (eg1 <= eg2) {
        for (int cr = eg1+1; cr <= eg2; ++cr) {
          pol.push_back(pixel[cr]);
        }
      } else {
        for (int cr = eg1+1; cr < 4; ++cr) {
          pol.push_back(pixel[cr]);
        }
        for (int cr = 0; cr <= eg2; ++cr) {
          pol.push_back(pixel[cr]);
        }
      }
    }
  }

  // should dbg pol

  pol = removedups(pol);

  dbg(pol.size());
  for (Point p : pol) {
    dbg(p.x,p.y);
  }

  pll res = polygonArea2(pol);
  res.F *= -1;
  res.S *= 2;
  rf(res);

  cout << res.F << '/' << res.S << "\n";
}

void solve()
{
  cin >> N; int q; cin >> q;
  vector<P> points;
  rep(i,0,N) {
    ll x,y; cin >> x >> y;
    pll p1 = {2*x+1,2};
    pll p2 = {2*y+1,2};
    points.push_back(P(p1,p2));
  }
  reverse(all(points)); // clockwise order instead
  rep(i,0,q) {
    ll x,y; cin >> x >> y;
    test(points, x, y);
  }
}

int main()
{
  ios::sync_with_stdio(0); cin.tie(0);
  solve();
}