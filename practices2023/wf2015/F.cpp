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

template<typename T> inline T ceildiv(T a, T b) {return (a+b-1)/b;}

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

void run() {
    int r,c; cin >> r >> c;
    vector<string> grid(r);
    rep(i,0,r) cin >> grid[i];
    string tgt; cin >> tgt; tgt += '*';
    vector<vector<pii>> coords(256);
    vector<vector<vector<pii>>> adj1(r, vector<vector<pii>>(c));
    rep(i,0,r) {
        rep(j,0,c) {
            for (auto dir : dirs) {
                int nx = i+dir.F, ny = j+dir.S;
                while (nx >= 0 && ny >= 0 && nx < r && ny < c) {
                    if (grid[nx][ny] != grid[i][j]) {
                        adj1[i][j].pb({nx,ny});
                        break;
                    }
                    nx+=dir.F; ny +=dir.S;
                }
            }
        }
    }

    // vector<vector<vector<vector<pair<int,pii>>>>> adj(sz(tgt), vector<vector<vector<pair<int,pii>>>>(r, vector<vector<pair<int,pii>>>(c)));
    // rep(x,0,sz(tgt)) {
    //     rep(i,0,r) {
    //         rep(j,0,c) {
    //             for (auto p : adj1[i][j])
    //             adj[x][i][j].pb({x,p});
    //         }
    //     }
    // }
    // rep(x,0,sz(tgt)-1) {
    //     rep(i,0,r) {
    //         rep(j,0,c) {
    //             if (grid[i][j] == tgt[x])
    //             adj[x][i][j].pb({x+1,{i,j}});
    //         }
    //     }
    // }

    queue<pair<pii,pii>> q;
    vector<vector<vector<bool>>> vis(sz(tgt), vector<vector<bool>>(r, vector<bool>(c)));
    q.push({{0,0},{0,0}});
    vis[0][0][0] = 1;
    while (!q.empty()) {
        auto t = q.front(); q.pop();
        if (t.F.F == sz(tgt)-1 && grid[t.F.S][t.S.F] == '*') {
            print(1 + t.S.S);
            return;
        }
        for (auto p : adj1[t.F.S][t.S.F]) {
            if (vis[t.F.F][p.F][p.S]) continue;
            q.push({{t.F.F,p.F}, {p.S,t.S.S+1}});
            vis[t.F.F][p.F][p.S] = 1;
        }
        if (grid[t.F.S][t.S.F] == tgt[t.F.F]) {
            if (vis[t.F.F+1][t.F.S][t.S.F]) continue;
            q.push({{t.F.F+1,t.F.S}, {t.S.F,t.S.S+1}});
            vis[t.F.F+1][t.F.S][t.S.F] = 1;
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