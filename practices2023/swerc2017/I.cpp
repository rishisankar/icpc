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

ll n,m,N;
VVLL mat;

// helper func for matmodpow. assumes both are square matrices
VVLL matmul(VVLL& v1, VVLL& v2, ll mod) {
  int n = v1.size();
  VVLL res(n, VLL(n, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        res[i][j] += v1[i][k]*v2[k][j];
        res[i][j] %= mod;
      }
    }
  }
  return res;
}

// needs to be square matrix
// complexity: O(n^3 log(exp))
VVLL matmodpow(VVLL base, ll exp, ll mod) {
  int n = base.size();
  VVLL result(n,VLL(n,0));
  for(int i=0; i<n;++i)result[i][i]=1;
  while (exp > 0) {
    if (exp & 1) result = matmul(result,base,mod);
    base = matmul(base, base,mod);
    exp >>= 1;
  }
  return result;
}

void cnt(int mask, int nm, int fsf) {
    if (fsf == n) {
        mat[mask][nm]++;
        return;
    }
    if ((mask >> fsf) & 1) {
        // current filled, can't do anything
        return cnt(mask,nm,fsf+1);
    } else {
        // cases: 2x1 horiz, 1x1, 2x1 vert (if next unfilled + not last), 
        cnt(mask, nm, fsf+1); // 1x1 case
        cnt(mask, nm | (1 << fsf), fsf+1); // 2x1 horiz
        if (fsf != n-1 && ((mask >> (fsf+1))&1) == 0) {
            cnt(mask, nm, fsf+2);
        }
    }
}

void run() {
    cin >> n >> m;
    N = (1<<n);
    mat.resize(N, VLL(N));
    rep(mask,0,N) {
        cnt(mask, 0, 0);
    }
    dbg(mat);
    VVLL ans = matmodpow(mat, m, 1000000000LL);
    print(ans[0][0]);
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