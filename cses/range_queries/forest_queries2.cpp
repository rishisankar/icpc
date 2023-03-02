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

const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
// const ll mod = 998244353;

struct FenwickTree2D {
    typedef ll T;
    const T unit = 0;
    vector<vector<T>> bit;
    int n, m;

    FenwickTree2D(int n, int m) : n(n), m(m) {
        bit.resize(n, vector<T>(m,unit));
    }

    // sum 0<=i<=x, 0<=j<=y of v[i][j]
    T sum(int x, int y) {
        if (x<0||y<0)return 0;
        T ret = unit;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
                ret += bit[i][j];
        return ret;
    }

    /* sum of submatrix (assuming 0<=x1<=x2<n, 0<=y1<=y2<m) */
    T submatrixSum(int x1, int y1, int x2, int y2) {
        return sum(x2,y2) - sum(x1-1,y2) - sum(x2,y1-1) + sum(x1-1,y1-1);
    }

    // v[x][y]+=delta
    void add(int x, int y, T delta) {
        for (int i = x; i < n; i = i | (i + 1))
            for (int j = y; j < m; j = j | (j + 1))
                bit[i][j] += delta;
    }
};

void run() {
    int n, q; cin >> n >> q;
    VVI v(n,VI(n));
    rep(i,0,n) {
        string s; cin >> s;
        rep(j,0,n) {
            v[i][j] = (s[j] == '*' ? 1 : 0);
        }
    }
    FenwickTree2D ft(n,n);
    rep(i,0,n) {
        rep(j,0,n) {
            if (v[i][j]>0) ft.add(i,j,1);
        }
    }
    rep(i,0,q) {
        int t; cin >> t;
        if (t == 1) {
            int y,x; cin >> y >> x; --y; --x;
            if (v[y][x]) {
                ft.add(y,x,-1); v[y][x]=0;
            } else {
                ft.add(y,x,1); v[y][x]=1;
            }
        } else {
            int y1,x1,y2,x2; cin >> y1 >> x1 >> y2 >> x2;
            --y1; --x1; --y2; --x2;
            print(ft.submatrixSum(y1,x1,y2,x2));
        }
    }
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