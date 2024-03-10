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
typedef __float128 ld;
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
const ld INF = 7e12;
const ld EPS=1e-6;


void dijkstra(int s, ld angle, vector<ld> &d, vector<vector<pair<int, pair<ld,ld>>>> &adj) {
    int n = adj.size();
    d.assign(n, INF);

    d[s] = 0;
    using pdi = pair<ld, int>;
    priority_queue<pdi, vector<pdi>, greater<pdi>> q;
    q.push({(ld)0, s});
    while (!q.empty()) {
        int v = q.top().second;
        ld d_v = q.top().first;
        q.pop();
        if (d_v != d[v])
            continue;

        for (auto edge : adj[v]) {
            int to = edge.first;
            ld len = edge.second.first;
            ld th = edge.second.second;

            dbg(v,edge,angle);

            if(th>angle) continue;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                q.push({d[to], to});
            }
        }
    }
}

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


ld theta(pii p, pii q, pii r)
{
  ld MX = max(max(max(p.F, p.S), max(q.F,q.S)), max(r.F,r.S));
  Point<ld> pp(p.F/MX,p.S/MX);
  Point<ld> qq(q.F/MX,q.S/MX);
  Point<ld> rr(r.F/MX,r.S/MX);
  Point<ld> qp = qq-pp;
  Point<ld> rq = rr-qq;
  ld qpdist = qp.dist();
  qp.x /= qpdist;
  qp.y /= qpdist;
  ld rqdist = rq.dist();
  rq.x /= rqdist;
  rq.y /= rqdist;
  ld a=acosl(qp.dot(rq));
  ld PI=atanl(1)*4;
  ld ans = (a*180)/PI;
  return min(ans,(ld)180);
}


void solve()
{
  // graph has n*n nodes (cur,par)
  int n,m;
  ld D; long double D_;
  cin>>n>>m>>D_; D = D_;

  vector<pii> pts(n);
  rep(i,0,n) cin>>pts[i].F>>pts[i].S;

  vector<vector<pair<int,pair<ld,ld>>>> g(n*n+1); // n*n is for super source

  rep(i,0,m)
  {
    int a,b;
    cin>>a>>b;
    a--;b--;
    // now go and add that edge everywhere
    ld dist=sqrtl(((pts[a].F-pts[b].F)/D)*((ld)(pts[a].F-pts[b].F)/D)+((pts[a].S-pts[b].S)/D)*((ld)(pts[a].S-pts[b].S)/D));
    rep(p,0,n)
    {
      if(p==a) continue;
      ld th=theta(pts[p],pts[a],pts[b]);
      dbg(pts[p],pts[a],pts[b],th);
      g[a*n+p].pb(mp(b*n+a,mp(dist,th)));
    }

    if(a==0) // then add special super source edges
    {
      g[n*n].pb(mp(b*n+a,mp(dist,0)));
    }
  }


  ld l=0,r=190;
  bool found=false;
  rep(z,0,200)
  {
    ld m=(l+r)/2;
    vector<ld> d(n*n+1);
    dijkstra(n*n,m,d,g);

    ld best=INF;
    rep(p,0,n)
    best=min(best,d[(n-1)*n+p]);

    dbg(m,best);
    dbg(d);

    if(best<1+EPS*9/10)
    {r=m; found=true;}
    else
    l=m;
  }
  long double ANS = r;

  if(found)
  printf("%.20Lf\n",ANS);
  else
  printf("Impossible\n");



}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  ll t=1;

  rep(i,0,t)
    solve();
}
