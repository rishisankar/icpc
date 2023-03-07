#pragma GCC optimize("Ofast")

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

ll m1[100][100] = {};
ll m2[100][100] = {};
ll m3[100][100] = {};

inline void matmul(ll (*v1)[100], ll (*v2)[100], ll (*res)[100]) {
  rep(i,0,100) { rep(j,0,100) { res[i][j] = -1; }}
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      for (int k = 0; k < 100; ++k) {
        if (v1[i][k] != -1 && v2[k][j] != -1) {
            if (res[i][j] == -1 || res[i][j] > v1[i][k]+v2[k][j]) res[i][j] = v1[i][k] + v2[k][j];
        }
      }
    }
  }
}

/*
Initially: (0,INF,...)  --> min path len to i with exactly 0 edges


ith row of matrix: 1 if path going to i from j

dist(a,b,k) = dist(a,i,k/2) + dist(i,b,k/2)

1 2  1 2
3 4  3 4  

*/
void run() {
    int n,m,k; cin >> n >> m >> k;
    rep(i,0,100) rep(j,0,100) m1[i][j] = -1;
    rep(i,0,m) {
        int a,b; cin >> a >> b;
        ll c; cin >> c;
        if (m1[a-1][b-1] == -1 || m1[a-1][b-1] > c) m1[a-1][b-1] = c;
    }
    ll (*base)[100] = m1;
    ll (*result)[100] = m2;
    ll (*mul)[100] = m3;

    rep(i,0,100) {
        rep(j,0,100) {
            if (i != j) result[i][j] = -1;
        }
    }

    while (k) {
        if (k & 1) {
            matmul(result, base, mul);
            swap(result, mul);
        }
        matmul(base, base, mul);
        swap(base,mul);
        k >>= 1;
    }

    print(result[0][n-1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    // ll t; cin >> t;
    ll t=1;
    rep(tests,0,t) run();
}