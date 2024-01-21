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

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) { x += 0x9e3779b97f4a7c15; x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9; x = (x ^ (x >> 27)) * 0x94d049bb133111eb; return x ^ (x >> 31); }
    size_t operator()(uint64_t x) const { static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count(); return splitmix64(x + FIXED_RANDOM); }
};
template<typename T, typename U> struct safe_map : public std::unordered_map<T,U,custom_hash> {};
template<typename T> struct safe_set : public std::unordered_set<T,custom_hash> {};

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

template<class T>
struct SubMatrix {
	vector<vector<T>> p;
	SubMatrix(vector<vector<T>>& v) {
		int R = sz(v), C = sz(v[0]);
		p.assign(R+1, vector<T>(C+1));
		rep(r,0,R) rep(c,0,C)
			p[r+1][c+1] = (v[r][c] + p[r][c+1] + p[r+1][c] - p[r][c] + mod*5) % mod;
	}
	T sum(int u, int l, int d, int r) {
		return ((p[d][r] - p[d][l] - p[u][r] + p[u][l]) + mod*5 ) % mod;
	}
};

typedef SubMatrix<ll> SM;

const int MX = 10;
void run() {
    int n; cin >> n;
    vector<pii> inp(n);
    rep(i,0,n) cin >> inp[i].F >> inp[i].S;
    ll sc = (n % 2 == 1) ? (inp[n/2].S - inp[n/2].F + 1) : 1;
    if (n == 1) {
        print(sc);
        return;
    }
    vector<pii> linv(n/2), rinv(n/2);
    rep(i,0,n/2) {
        linv[i] = inp[i];
        rinv[i] = inp[n-1-i];
    }

    vector<vector<ll>> s1(MX, VLL(MX));
    rep(i,linv[0].F, linv[0].S + 1) {
        rep(j, rinv[0].F, rinv[0].S + 1) {
            s1[i][j] = 1;
        }
    }
    rep(i,0,MX) s1[i][i] = 0;
    SM cur(s1);
    rep(L,1,n/2) {
        int a = linv[L].F, b = linv[L].S, c = rinv[L].F, d = rinv[L].S;
        dbg(L,a,b,c,d);
        vector<vector<ll>> dp(MX, VLL(MX));
        rep(i,0,MX) {
            rep(j,0,MX) {
                int lx = max(i - b, 0);
                int rx = max(i - a, 0);
                int ly = max(j - d, 0);
                int ry = max(j - c, 0);
                // if (i == 3 && j == 13)  {
                //     dbg(lx,rx,ly,ry, cur.sum(lx,ly,rx+1,ry+1));
                // }
                dp[i][j] = cur.sum(lx,ly,rx+1,ry+1);
            }
        }
        rep(i,0,MX) dp[i][i] = 0;
        // dbg(L, dp);
        if (L == n/2 - 1) {
            ll ans = 0;
            rep(i,0,MX) {
                rep(j,0,MX) {
                    if (dp[i][j]) dbg(i,j);
                    ans += dp[i][j];
                    ans %= mod;
                }
            }
            print((ans*sc)%mod);
            return;
        }
        
        cur = SM(dp);
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