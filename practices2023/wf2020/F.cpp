#pragma GCC optimize("Ofast,inline")
#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define F first
#define S second
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '{'; string sep; for (const auto &x : v) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef NIKIL_DEBUG
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

const int MOD = 1000000000 + 7;
const ld EPS=1e-6;

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
	ld angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

typedef Point<ll> P;

template<class P>
ld lineDist(const P& a, const P& b, const P& p) {
	return (ld)(b-a).cross(p-a)/(b-a).dist();
}


ll T;

inline bool inRange(const P& a, const P& b, const P& p)
{
  ld d=lineDist(a,b,p);
  return (d>-EPS && d<T+EPS);
}


ll sweep(int pivot, vector<P> &pts)
{
  // dbg("Sweeping ",pivot);
  vector<pair<ld,int>> vv;
  P p=pts[pivot];
  rep(i,0,sz(pts)) if(i!=pivot) vv.pb(mp((pts[i]-p).angle(),i));
  sort(all(vv));

  vector<P> v;
  trav(a,vv) v.pb(pts[a.S]);
  // sort(all(v),[&](P a, P b){return (a-p).angle()<(b-p).angle();});

  // dbg(v);

  // initially there will be some points that are already within t
  // everything else will come within t on some prefix of the array or never!
  int n=sz(v);
  vector<pii> events; // add first (0), query(1), delete yourself (2)
  rep(i,0,n) events.pb(mp(i,1));
  rep(i,0,n) events.pb(mp(i,2));

  // now find when everything that is not already active becomes active
  ll ct=0;
  rep(i,0,n)
  {
    if(inRange(p,v[0],v[i])) ct++;
    else
    {
      int l=0, r=i;
      int ans=r; // you definitely become active at least when it gets to you lol
      while(l<=r)
      {
        int m=(l+r)/2;
        if(inRange(p,v[m],v[i]))
        {
          ans=min(ans,m);
          r=m-1;
        }
        else
        {
          l=m+1;
        }
      }

      // create event
      events.pb(mp(ans,0));
    }
  }
  // dbg(ct);

  ll best=1;

  // now sweep
  sort(all(events));
  trav(a,events)
  {
    if(a.S==0) ct++;
    if(a.S==1) best=max(best,ct);
    if(a.S==2) ct--;
    // dbg(a,ct);
  }

  return best+1;
}


// -0:54
void solve()
{
  int n;
  cin>>n>>T;

  vector<P> pts(n);
  rep(i,0,n) cin>>pts[i].x>>pts[i].y;

  // dbg(pts);

  // do a sweep from each point
  ll best=1;
  rep(i,0,n)
  best=max(best,sweep(i,pts));

  rep(i,0,n) pts[i]=pts[i].perp().perp();
  rep(i,0,n)
  best=max(best,sweep(i,pts));

  cout<<best<<"\n";
}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  ll t=1;

  rep(i,0,t)
    solve();
}
