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

VPII dirs{mp(-1,0),mp(1,0),mp(0,-1),mp(0,1), mp(1,1), mp(1,-1), mp(-1,1), mp(-1,-1)};
const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
// const ll mod = 998244353;

int n,n1,nr;
VVI adjr,adj1;

void run() {
    cin >> n;
    if (n == 1) {
        print(0);
        return;
    }
    vector<vector<int>> grid(n+2, vi(n+2));
    int c = 1;
    for (int i = n+1; i >= 0; --i) grid[i][0] = c++;
    for (int j = 1; j <= n; ++j) grid[0][j] = c++;
    for (int i = 0; i < n+2; ++i) grid[i][n+1] = c++;
    for (int j = n; j >= 1; --j) grid[n+1][j] = c++;
    c = -1;
    for (int i = n; i >= 1; --i) grid[i][1] = c--;
    for (int j = 2; j <= n-1; ++j) grid[1][j] = c--;
    for (int i = 1; i <= n; ++i) grid[i][n] = c--;
    for (int j = n-1; j >= 2; --j) grid[n][j] = c--;
    
    n1 = 4*n-4;
    nr = 4*n+4;
    
    adjr.resize(nr+1);
    adj1.resize(n1+1);
    rep(i,0,n+2) {
        rep(j,0,n+2) {
            if (grid[i][j] == 0) continue;
            if (grid[i][j] < 0) {
                for (auto p : dirs) {
                    int nx = i+p.F, ny = j+p.S;
                    if (nx < 0 || ny < 0 || nx >= n+2 || ny >= n+2 || grid[nx][ny] <= 0) continue;
                    adj1[-grid[i][j]].pb(grid[nx][ny]);
                }
            } else {
                for (auto p : dirs) {
                    int nx = i+p.F, ny = j+p.S;
                    if (nx < 0 || ny < 0 || nx >= n+2 || ny >= n+2 || grid[nx][ny] >= 0) continue;
                    adjr[grid[i][j]].pb(-grid[nx][ny]);
                }
            }
        }
    }

    vi r1o, r2o, r3o, r4o;
    rep(i,1,5) r1o.pb(i);
    rep(i,n+2,n+6) r2o.pb(i);
    rep(i,2*n+3,2*n+7) r3o.pb(i);
    rep(i,3*n+4,3*n+8) r4o.pb(i);


    vector<bool> isSafe(nr+1, 1);

    for (int r1 : r1o) {
        for (int r2 : r2o) {
            for (int r3 : r3o) {
                for (int r4 : r4o) {
                    bool ok = 1;
                    vector<bool> state(nr+1);
                    int cz = r1;
                    while (cz < n+2) {
                        state[cz] = 1;
                        cz += 3;
                    }
                    cz = r2;
                    while (cz < 2*n+3) {
                        state[cz] = 1;
                        cz += 3;
                    }
                    cz = r3;
                    while (cz < 3*n+4) {
                        state[cz] = 1;
                        cz += 3;
                    }
                    cz = r4;
                    while (cz < 4*n+5) {
                        state[cz] = 1;
                        cz += 3;
                    }
                    rep(i, 1, n1+1) {
                        int ct = 0;
                        for (int x : adj1[i]) ct += state[x];
                        if (ct != 1) {
                            ok = 0;
                            break;
                        }
                    }
                    if (ok) {
                        rep(i, 1, nr+1) {
                            if (state[i]) {
                                isSafe[i] = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    VI ans;
    rep(i,1,nr+1) if (isSafe[i]) ans.pb(i);
    print(sz(ans));
    for (int i : ans) cout << i << ' ';
    cout << '\n';

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