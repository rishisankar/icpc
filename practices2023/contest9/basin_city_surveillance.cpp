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

VVI adj;
VVB adjm;
int n,k;

typedef pair<ull,ull> M;

inline bool test(M& m, int p) {
    if (p < 64) return (m.S>>p)&1;
    else return (m.F>>(p-64))&1;
}

inline void reset(M& m, int p) {
    ull bs = 1;
    if (p < 64) m.S &= (~(bs << p));
    else m.F &= (~(bs << (p-64)));
}

bool test(int k, M& mask) {
    if (k <= 0) return true;
    // pick vertex v to start
    int v = -1;
    rep(i,0,n) {
        if (test(mask,i)) { v=i; break; }
    }
    if (v == -1) return false;
    // case 1: try removing v
    M mask2; mask2.F=mask.F; mask2.S=mask.S;
    reset(mask2,v);
    for (int a : adj[v]) {
        reset(mask2,a); // can't pick any neighbor
    }
    if (test(k-1, mask2)) return true;
    // case 2: try removing pairs of two neighbors
    rep(i,0,adj[v].size()) {
        rep(j,i+1, adj[v].size()) {
            int a = adj[v][i]; int b = adj[v][j];
            if (!(test(mask,a) && test(mask,b))) continue;
            if (adjm[a][b]) continue;
            M maskp; maskp.F=mask.F; maskp.S=mask.S;
            reset(maskp,a);
            reset(maskp,b);
            for (int c : adj[a]) reset(maskp,c);
            for (int c : adj[b]) reset(maskp,c);
            if (test(k-2,maskp)) return true;
        }
    }
    return false;
}

void run() {
    cin >> k >> n;
    adj.resize(n);
    rep(i,0,n) {
        int d; cin >> d;
        rep(j,0,d) {
            int a; cin >> a; --a;
            adj[i].pb(a);
        }
    }
    if (n >= 5*k) { print("possible"); return; }
    if (k > n) { print("impossible"); return; }
    adjm.resize(n,vector<bool>(n,false));
    rep(i,0,n) {
        for (int a : adj[i]) {
            adjm[i][a] = true;
        }
    }

    M m = {0,0};
    m.F = ~m.F; m.S = ~m.S;
    if (test(k, m)) print("possible");
    else print("impossible");
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