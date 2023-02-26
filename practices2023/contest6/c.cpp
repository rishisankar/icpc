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

typedef  vector<double> vd;
const double eps = 1e-12;

int solveLinear(vector<vd>& A, vd&b , vd&x) {
  int n = sz(A), m=sz(x), rank = 0, br, bc;
  if(n) assert(sz(A[0]) == m);
  vi col(m); iota(all(col), 0);
  rep(i, 0, n) {
    double v, bv = 0;
    rep(r,i,n) rep(c,i,m)
      if((v = fabs(A[r][c])) > bv)
      br = r, bc = c, bv = v;
    if(bv <= eps) {
      rep(j, i, n) if(fabs(b[j]) > eps) return -1;
      break;
    }
    swap(A[i], A[br]);
    swap(b[i], b[br]);
    swap(col[i], col[bc]);
    rep(j,0,n) swap(A[j][i], A[j][bc]);
    bv = 1/A[i][i];
    rep(j,i+1,n) {
      double fac = A[j][i] * bv;
      b[j] -= fac * b[i];
      rep(k, i+1,m) A[j][k] -= fac*A[i][k];
    }
    rank++;
  }

  x.assign(m, 0);
  for(int i = rank; i--;) {
    b[i] /= A[i][i];
    x[col[i]] = b[i];
    rep(j,0,i) b[j] -= A[j][i] * b[i];
  }
  return rank;
}


const int MOD = 1e9+7;
void solve()
{
  int dl,dw,G,L;
  cin>>dl>>dw>>G>>L;

  double g=G/(double)100;
  double l=L/(double)100;

  vector<vd> A(101,vd(101,0));
  vd B(101,1);
  rep(i,0,101)
  {
    double p=i/(double)100;
    // dbg(p,g,l);
    A[i][i]=1;
    A[i][0]-=(1-l)*p*(1-g);
    int x=min(i+dw,100);
    A[i][x]-=(1-l)*(1-p);
    int y=min(i+dl,100);
    A[i][y]-=l;
    // dbg(x,y);
  }

  // dbg(A);


  vd x(101,0);
  int res=solveLinear(A,B,x);
  // dbg(res);
  cout<<fixed<<setprecision(20)<<x[0]<<"\n";


}

int main()
{
  solve();
}