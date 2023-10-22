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

VPII dirs{mp(1,0),mp(0,1)};
const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
// const ll mod = 998244353;

void fail() {
    print("Impossible");
}

void bf(int n, int k) {
    int N = n*n;
    rep(msk,0,(1<<N)) {
        vector<string> ans(n, string(n, 'R'));
        rep(i,0,n) {
            rep(j,0,n) {
                int idx = i*n+j;
                if ((msk >> idx) &1) ans[i][j] = 'B';
            }
        }
        int ct = 0;
        rep(i,0,n) {
            rep(j,0,n) {
                for (pii p : dirs) {
                    int ni = i+p.F, nj = j+p.S;
                    if (ni >= 0 && nj >= 0 && ni < n && nj < n) {
                        if (ans[i][j] != ans[ni][nj]) ++ct;
                    }
                }
            }
        }
        if (ct == k) {
            print("Possible");
            for (string s : ans) print(s);
            return;
        }
    }
    fail();
}

inline bool iscorner(int n, int i, int j) {
    return (i == 0 || i == n-1) && (j == 0 || j == n-1);
}

inline bool isedge(int n, int i, int j) {
    return !iscorner(n,i,j) && (i == 0 || i == n-1 || j == 0 || j == n-1);
}

bool check(int k, int n2, int n3, int n4, int& u2, int& u3, int& u4) {
    u2 = n2; u3 = n3; u4 = n4;
    if (k == 1) return false;
    if (k & 1) {
        n3--; k-=3;
    }
    while (n3 >= 2 && k >= 6) {
        n3-=2; k-=6;
    }
    while (n4 >= 1 && k >= 4) {
        n4--; k-=4;
    }
    while (n2 >= 1 && k >= 2) {
        n2--; k-=2;
    }
    if (k != 0) return false;
    u2 -= n2; u3 -= n3; u4 -= n4;
    return true;
}

void run() {
    int n,k; cin >> n >> k;
    if (n < 4) return bf(n,k);
    if (k == 1) return fail();

    vector<vector<pii>> graph(5);
    rep(i,0,n) {
        rep(j,0,n) {
            if (((i+j) & 1) == 0) {
                if (iscorner(n,i,j)) graph[2].pb({i,j});
                else if (isedge(n,i,j)) graph[3].pb({i,j});
                else graph[4].pb({i,j});
            }
        }
    }
    int n2 = sz(graph[2]);
    int n3 = sz(graph[3]);
    int n4 = sz(graph[4]);
    dbg(n2,n3,n4);
    int u2,u3,u4;
    if (!check(k,n2,n3,n4,u2,u3,u4)) return fail();
    dbg(u2,u3,u4);
    print("Possible");
    vector<string> ans(n, string(n, 'R'));
    vector<pii> blues;
    rep(i,0,u2) blues.pb(graph[2][i]);
    rep(i,0,u3) blues.pb(graph[3][i]);
    rep(i,0,u4) blues.pb(graph[4][i]);
    for (pii p : blues) ans[p.F][p.S] = 'B';
    for (string s : ans) print(s);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    ll t; cin >> t;
    // ll t=1;
    rep(tests,0,t) run();
}