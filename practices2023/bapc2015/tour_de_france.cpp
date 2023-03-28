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

const ull one = 1;

void gen(int d, ull mask, int s, int c, vector<unordered_map<ull, int>>& paths, VVPII& adj) {
    if (d == 0) {
        if (paths[s].count(mask)) paths[s][mask] = min(paths[s][mask], c);
        else paths[s][mask] = c;
        return;
    }
    for (pii p : adj[s]) {
        if (((mask >> p.F) & 1) == 0) { // ensure unused
            if (p.F == 0 && d != 1) continue;
            gen(d-1, (mask ^ (one << p.F)), p.F, p.S+c, paths, adj);
        }
    }
}

/*
generate all paths of dist d (# edges) >= 0, start node s
*/
inline void genPath(int d, int s, vector<unordered_map<ull, int>>& paths, VVPII& adj) {
    gen(d, (one<<s), s, 0, paths, adj);
}

void run() {
    int n,m; cin >> n >> m;
    VVPII adj(n);
    VVPII radj(n);
    rep(i,0,m) {
        int a,b,c; cin >> a >> b >> c;
        adj[a].pb({b,c});
        radj[b].pb({a,c});
    }
    vector<unordered_map<ull, int>> paths(n); // for each end node, bitmask --> best cost
    vector<unordered_map<ull, int>> rpaths(n);
    genPath(n/2, 0, paths, adj);
    genPath((n+1)/2, 0, rpaths, radj);
    vector<vector<pair<ull,int>>> paths_ur(n);
    for (int md = 1; md < n; ++md) {
        for (auto p : paths[md]) {
            paths_ur[md].pb(p);
        }
    }
    rep(i,0,n) for (auto p : paths[i]) dbg(i, bitset<6>(p.F).to_string(), p.S);

    // start node 0
    int bst = INT_MAX;
    ull gl = (one << n)-1;
    for (int md = 1; md < n; ++md) {
        // vector<unordered_map<ull, int>> p2(n);
        // genPath((n+1)/2, md, p2, adj);
        for (auto p : paths_ur[md]) {
            ull bm = gl ^ p.F ^ 1 ^ (one << md);
            dbg(bitset<6>(bm).to_string());
            if (rpaths[md].count(bm)) {
                bst = min(bst, p.S + rpaths[md][bm]);
            }
        }
    }
    print(bst);
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