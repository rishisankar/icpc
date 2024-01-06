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

vector<vector<vector<pii>>> adj;
vector<vector<bool>> g;

void addAdj(int a, int b, int c, int d) {
    if (!g[a][b]) return;
    if (!g[c][d]) return;
    adj[a][b].pb({c,d});
    adj[c][d].pb({a,b});
}

void run() {
    int h,n,m; cin >> h >> n >> m;
    g.resize(n,VB(m));
    adj.resize(n, vector<VPII>(m));
    rep(i,0,n) {
        rep(j,0,m) {
            char c; cin >> c; if (c == '.') g[i][j] = 1;
        }
    }
    rep(i,1,n) {
        rep(j,0,m) {
            if (i&1) {
                addAdj(i,j,i-1,j);
                if (j!=m-1)addAdj(i,j,i-1,j+1);
            } else {
                addAdj(i,j,i-1,j);
                if (j!=0)addAdj(i,j,i-1,j-1);
            }
        }
    }
    rep(i,0,n) {
        rep(j,1,m) {
            addAdj(i,j,i,j-1);
        }
    }
    VI lengths;
    VVB vis(n, VB(m));
    rep(i,0,n) {
        rep(j,0,m) {
            if (vis[i][j]) continue;
            if (!g[i][j]) continue;
            stack<pii> s;
            s.push({i,j});
            vis[i][j] = 1;
            int ct = 1;
            while (!s.empty()) {
                pii t = s.top();
                s.pop();
                for (pii x : adj[t.F][t.S]) {
                    if (vis[x.F][x.S]) continue;
                    vis[x.F][x.S] = 1;
                    ++ct;
                    s.push(x);
                }
            }
            lengths.pb(ct);
        }
    }
    sort(all(lengths));
    dbg(lengths);
    int ans = 0, ind = sz(lengths)-1;
    while (h > 0) {
        h -= lengths[ind--];
        ++ans;
    }
    print(ans);

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